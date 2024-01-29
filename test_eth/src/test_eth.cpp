#include "../udpWrap/udpWrap.h"
#include <stdio.h>
#define IP_PC        "192.168.0.103" /*  */
#define PC_SEND		 "192.168.0.109"
#define PORT_PC                  3425

/* Указатель на чтение данных от РМО */
static int socketRMO;

int main()
{
    socketRMO = udpOpen(IP_PC,PORT_PC);
    if (socketRMO < 0)
    {
        printf("Failed to open udp PORT_IMIT_RMO channel\n");
        return -1;
    }

    int8_t mass=1;

    while(1)
    {
    	udpSend(socketRMO,PC_SEND,PORT_PC,&mass,sizeof(mass));
    	mass++;
    }

    return 0;
}

#if 0
int udpSend(int fd, char* ip, uint16_t port, void* pData, size_t len)
{
    int res = 0;

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip);
    address.sin_port = htons(port);

    res = sendto(fd, pData, len, 0, (struct sockaddr*)&address, sizeof(address));

    if (res != len)
    {
        printf("Failed to send \n");
        return -1;
    }
    return res;
}

int udpRecv(int fd, void* pData, size_t maxSize)
{
    int res = recv(fd, pData, maxSize, 0);

    return res;
}

int udpClose(int fd)
{
    return close(fd);
}

int udpOpen(char* ip, uint16_t port)
{
    int sockFD = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockFD < 0)
    {
        printf("Failed to create socket\n");
        return -1;
    }

    struct sockaddr_in address = {0};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = ip ? inet_addr(ip) : INADDR_ANY;
    address.sin_port = htons(port);
    //address.sin_len = sizeof(address);

    int rc = bind(sockFD, (struct sockaddr*)&address, sizeof(address));
    if (0 != rc)
    {
        printf("Failed to bind socket to %s:%d, errno=%d\n", ip, port, errno);
        return -1;
    }
    #ifdef WIN32
    u_long mode = 1;
    rc = ioctlsocket(sockFD, FIONBIO, &mode);
    #else
    rc = fcntl(sockFD, F_SETFL, O_NONBLOCK);
    #endif
    if (0 != rc)
    {
        printf("Failed to set NON BLOCKING mode for %s:%d, rc=%d, errno=%d,\n", ip,
        port, rc, errno);
        udpClose(sockFD);
        return -1;
    }

    printf("Socket %d binded to %s:%d in NON BLOCKING mode\n", sockFD, ip, port);
    return sockFD;
}
#endif
