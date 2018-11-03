#ifndef _NETWORKING_H
#define _NETWORKING_H

#define PING_TIMEOUT_MS 15000

#include <Ethernet.h>

#define NETWORK 192, 168, 99
#define MASK 255,255,255,0
#define LISTEN_PORT 6666
#define LOXONE_PORT 5555
const IPAddress SEND_IP_ADDRESS(192,168,99,255);



#define recvBufferSize 64
#define sendBufferSize 64

void initNetwork(int mainBoardId);
void send(char* msg);
bool receiveMessage(char* buffer, int bufferSize);

#endif
