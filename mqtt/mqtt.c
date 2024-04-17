#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 48907


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

int main()
{
    printf("hola\n");
    struct sockaddr_in addr;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sConnect *conect = malloc(sizeof(sConnect));

    memset(&addr, 0, sizeof(addr));

    inet_pton(AF_INET, "192.168.1.17", &(addr.sin_addr));
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    int ret = connect(sock, (const struct sockaddr*)&addr, sizeof(addr));
    // send connect command
    conect->bFrameType = 0x10;
    conect->wMsgLen = 0x11;
    conect->wProtlNameLen = 0x0004;
    strcpy(conect->sProtName, "MQTT");
    conect->bVersion = 0x05;
    conect->bConnectFlags = 0x02;
    conect->bKeepAlive = 0x003C;
    conect->wClientIdLen = 0x05;
    strcpy(conect->sProtName, "test");

    //char buff[1024];
    ret = send(sock, conect, sizeof(sConnect), 0);
    //ret = recv(sock, buff, 1024*sizeof(char), 0);
    //printf("%X", buff);

    ret = close(sock);

    return 0;
}
