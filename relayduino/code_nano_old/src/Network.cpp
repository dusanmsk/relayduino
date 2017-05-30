
#include "Network.h"
#include "UIPEthernet.h"
#include "dbg.h"

void Network::zeroRecvBuffer() {
  memset(recvBuf, '\0', NET_BUF_SIZE);
}

void Network::begin(uint8_t mac[], IPAddress address) {
  Ethernet.begin(mac, address);
  udpRecv.begin(5555);
  tcpServer.begin();
}

void Network::sendUdp(IPAddress address, int port, String message) {
  zeroSendBuffer();
  message.toCharArray(sendBuf, NET_BUF_SIZE, 0);
  //dbgf("Sending '%s'" , buf);
  udpSend.beginPacket(address, port);
  udpSend.write(sendBuf, message.length());
  udpSend.endPacket();
  udpSend.flush();
  //dbg("Sent");
}

bool Network::receiveTcp(int port) {
  size_t size;
  if(EthernetClient client = tcpServer.available()) {
    if((size = client.available()) > 0) {
        dbgf("read %d", size);
         client.read(recvBuf, NET_BUF_SIZE);
         client.write("ok");
    }
    client.stop();
    return true;
  }
  return false;
}

bool Network::receiveUdp(int port) {

  int size = udpRecv.parsePacket();
  //dbgf("Parsed: %d", size);
  if(size > 0) {
      zeroRecvBuffer();
      int how = udpRecv.read(recvBuf, NET_BUF_SIZE);
      //dbgf("Read %s", how);
      return true;
  }
  return false;
}
