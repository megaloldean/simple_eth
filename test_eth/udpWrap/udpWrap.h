/*
 * udpWrap.h
 *
 *  Created on: 28 янв. 2024 г.
 *      Author: root
 */

#ifndef UDPWRAP_H_
#define UDPWRAP_H_


#include "stdint.h"
#include "stddef.h"

int udpInit(void);
int udpOpen(char* ip, uint16_t port);
int udpSend(int fd, char* ip, uint16_t port, void* pData, size_t len);
int udpRecv(int fd, void* pData, size_t maxSize);
int udpClose(int fd);


#endif /* UDPWRAP_H_ */
