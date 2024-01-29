#include "udpWrap.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef WIN32
#include "windows.h"
#else
#include <sys/socket.h>
#include "netinet/in.h"
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#endif

#ifdef WIN32
WSADATA dataWsa;
#endif


int udpInit(void)
{
#ifdef WIN32
    int wsaErr;
    wsaErr = WSAStartup(MAKEWORD(2, 2), &dataWsa);
    if (0 != wsaErr)
    {
        printf("WSAstartup failed with error %d\r\n", wsaErr);
        return -1;
    }
#endif

    return 0;
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
        printf("Failed to set NON BLOCKING mode for %s:%d \n", ip,
        port);
        udpClose(sockFD);
        return -1;
    }

    printf("Socket %d binded to %s:%d in NON BLOCKING mode\n", sockFD, ip, port);
    return sockFD;
}

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
        printf("Failed to send %u bytes to %s:%u (error %s(%d))\n",
                len, ip, port, strerror(errno), errno);
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
