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
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));


    
    puts("Server listening");
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);

    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);


    //recv
    char recvStr[STR_MAX] = "";
    read(clnt_sock, recvStr, sizeof(recvStr)-1);
    printf("Message: %s\n", recvStr);

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
    write(clnt_sock, response, STR_MAX-1);
   
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);
    return 0;
}
