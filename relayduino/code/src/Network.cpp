
#include "Network.h"
#include "UIPEthernet.h"
#include "dbg.h"

void Network::zeroBuffer() {
  memset(buf, '\0', NET_BUF_SIZE);
}

void Network::begin(uint8_t mac[], IPAddress address) {
  Ethernet.begin(mac, address);
}

void Network::sendUdp(IPAddress address, int port, String message) {
  zeroBuffer();
  message.toCharArray(buf, NET_BUF_SIZE, 0);
  //dbgf("Sending '%s'" , buf);
  udpSend.beginPacket(address, port);
  udpSend.write(buf, message.length());
  udpSend.endPacket();
  udpSend.flush();
  //dbg("Sent");
}

bool Network::receiveUdp(int port) {
  udpRecv.begin(port);
  int size = udpRecv.parsePacket();
  //dbgf("Parsed: %d", size);
  if(size > 0) {
      zeroBuffer();
      int how = udpRecv.read(buf, NET_BUF_SIZE);
      //dbgf("Read %s", how);
      receivedPacket = String((char*)buf);
      return true;
  }
  udpRecv.stop();
  return false;
}
