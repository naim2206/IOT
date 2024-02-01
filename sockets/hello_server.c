#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 3000

int main(int argc, char const* argv[])
{

    struct sockaddr_in addr;

    // Dominio internet, TCP, protocolo automatico
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    memset(&addr, 0, sizeof(addr));

    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    bind(sock, (const struct sockaddr*)&addr, sizeof(addr));

    listen(sock, 10);

    for (;;)
    {
        int client = accept(sock, (const struct sockaddr*)NULL, NULL);
        send(client, "Hola ITESO\n", strlen("Hola ITESO\n"), 0);
        puts("hice algo");
        close(client);
    }


    return 0;
}
