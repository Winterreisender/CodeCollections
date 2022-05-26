// Linux

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define STR_MAX 64

int main(void){
    //创建套接字
    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr = {};
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口

   // send
    char queryStr[STR_MAX] = "";
    puts("input id:");
    gets(queryStr);
    printf("Client sending %s\n", queryStr);
    sendto(sock, queryStr, strlen(queryStr),0,&serv_addr,sizeof(serv_addr));

    //读取服务器传回的数据
    char recvStr[STR_MAX] = "";
    int len = sizeof(serv_addr);
    puts("Waiting server response");
    recvfrom(sock, recvStr, sizeof(recvStr), 0, NULL, NULL);
    
    printf("Client received(%d): %s\n",len, recvStr);

    //关闭套接字
    close(sock);
    return 0;
}