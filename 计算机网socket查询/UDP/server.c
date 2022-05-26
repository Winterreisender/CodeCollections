#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define STR_MAX 64


struct Student
{
    char id[STR_MAX];
    char name[STR_MAX];
    char class[STR_MAX];
};


#define DB_LEN 3
struct Student Students[DB_LEN]  = 
{
    {
        "1", //学号
        "Name1", //姓名
        "Class1" //班级
    },
    {
        "2",
        "Name2",
        "Class2"
    },
    {
        "3",
        "Name3",
        "Class3"
    },
};

int lookup(const char* id)
{
    for(int i=0; i< DB_LEN; i++)
        if(strcmp(Students[i].id, id) == 0)
            return i;
    return -1;
}

int main(void)
{
    //创建套接字
    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr = {};
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    struct sockaddr_in from_addr = {};
    memset(&from_addr, 0, sizeof(from_addr));  //每个字节都用0填充

    //recv
    char recvStr[STR_MAX] = "";
    int len = sizeof(from_addr);
    recvfrom(sock, recvStr, sizeof(recvStr), 0, (struct sockaddr *) &from_addr, &len);
    printf("Message: %s\n", recvStr);
    printf("Len: %d\n", len);
    printf("Client port: %d\n", from_addr.sin_port);

    //lookup
    const char* responseNotFound = "Not Found";
    char* response = responseNotFound;
    int index = lookup(recvStr);
    if(index >= 0)
    {
        response = &Students[index].name;
        printf("server found : %d\n", index);
    }


    //向客户端发送数据
    printf("Sending : %s\n", response);
    sleep(1);
    sendto(sock, response, strlen(response), 0, (struct sockaddr *) &from_addr, sizeof(from_addr));
    

    //关闭套接字
    close(sock);
    return 0;
}
