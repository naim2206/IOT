#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 3000
#define TIMES 5
#define SIZE 100


struct connectComand
{
    int keepAlive;
    int data;
}

int main(int argc, char const* argv[])
{
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    *struct connectComand connect;
    connect = malloc(sizeof(struct connectComand));

    memset(&addr, 0, sizeof(addr));

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    int ret = connect(sock, (const struct sockaddr*)&addr, sizeof(addr));
    // send connect command
    connect->keepAlive = 1;
    connect->data = 1;
    ret = send(sock, (void*)connect, sizeof(struct connectComand), 0);
    ret = recv(sock, (void*)buff, SIZE, 0);
    printf("Rx: %d\n", ret);
    printf("%s", buff);

    ret = close(sock);

    return 0;
}