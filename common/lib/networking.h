#ifndef _NETWORKING_H
#define _NETWORKING_H

#define PING_TIMEOUT_MS 15000

#include <Ethernet.h>

#define NETWORK 192, 168, 88
#define MASK 255,255,255,0
#define RECV_LOCAL_PORT 6666
#define SEND_LOCAL_PORT 6667
#define LOXONE_PORT 5555
#define SEND_IP_ADDRESS "255.255.255.255"



#define recvBufferSize UDP_TX_PACKET_MAX_SIZE
#define outputPacketBufferSize 128

void initNetwork(int mainBoardId);
void send(char* msg);
boolean receive(char* buffer, int bufferSize);

#endif
