
#ifndef _NETWORK_H
#define _NETWORK_H

#include "UIPEthernet.h"
#include "Arduino.h"
#include <avr/io.h>

#define NET_BUF_SIZE 64


class Network {
private:
  String receivedPacket;
  char buf[NET_BUF_SIZE];
  EthernetUDP udpSend;
  EthernetUDP udpRecv;
  void zeroBuffer();
  public:
     void begin(uint8_t mac[], IPAddress address);
     void sendUdp(IPAddress address, int port, String message);
     bool receiveUdp(int port);
     String getReceivedPacket() { return receivedPacket; }
};


#endif
