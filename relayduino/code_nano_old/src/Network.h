
#ifndef _NETWORK_H
#define _NETWORK_H

#include "UIPEthernet.h"
#include "Arduino.h"
#include <avr/io.h>

#define NET_BUF_SIZE 64


class Network {
private:
  char recvBuf[NET_BUF_SIZE];
  char sendBuf[NET_BUF_SIZE];
  EthernetUDP udpSend;
  EthernetUDP udpRecv;
  EthernetServer tcpServer = EthernetServer(6666);
  void zeroRecvBuffer();
  void zeroSendBuffer();
  public:
     void begin(uint8_t mac[], IPAddress address);
     void sendUdp(IPAddress address, int port, String message);
     bool receiveUdp(int port);
     bool receiveTcp(int port);
     const char* getReceivedPacket() {return (const char*) &recvBuf; };
};


#endif
