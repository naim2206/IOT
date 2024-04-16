#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 1883


typedef struct
{
    uint8_t bFrameType;
    uint16_t wMsgLen;
    uint16_t wProtlNameLen;
    char sProtName[4];
    uint8_t bVersion;
    uint8_t bConnectFlags;
    uint16_t bKeepAlive;
    uint16_t wClientIdLen;
    char sClientID[100];
} sConnect;

int main(int argc, char const* argv[])
{
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    *sConnect connect = malloc(sizeof(struct connectComand));

    memset(&addr, 0, sizeof(addr));

    inet_pton(AF_INET, "192.168.1.17", &(client.sin_addr));
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    int ret = connect(sock, (const struct sockaddr*)&addr, sizeof(addr));
    // send connect command
    connect->bFrameType = 0x10;
    connect->wMsgLen = 0x0006;
    connect->wProtlNameLen = 0x0004;
    connect->sProtName = "MQTT";
    connect->bVersion = 0x04;
    connect->bConnectFlags = 0x02;
    connect->bKeepAlive = 0x000A;
    connect->wClientIdLen = 0x0004;
    connect->sClientID = "test";

    char buff[1024];
    ret = send(sock, (void*)connect, sizeof(struct connectComand), 0);
    ret = recv(sock, buff, SIZE, 0);
    printf("%X", buff);

    ret = close(sock);

    return 0;
}