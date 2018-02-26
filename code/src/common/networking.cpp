
#include "networking.h"
#include "dbg.h"

byte mac[6] = {  0xDE, 0xAD, 0xBE, 0xAA, 0xFE, 0x01 };
byte ip[4] = { NETWORK, 0 };
byte mask[4] = { MASK };

EthernetUDP udpSend;
EthernetUDP udpReceive;

void initNetwork(int addressOffset) {
  mac[5] += addressOffset;
  ip[3]+=addressOffset;
  Ethernet.begin(mac, ip, mask);
  udpSend.begin(SEND_LOCAL_PORT);
  udpReceive.begin(RECV_LOCAL_PORT);

  dbg("Assigned address: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

}

char outputPacketBuffer[outputPacketBufferSize];
void send(char* msg) {
  snprintf(outputPacketBuffer, outputPacketBufferSize, msg);
  udpSend.beginPacket(SEND_IP_ADDRESS, LOXONE_PORT);
  udpSend.write(outputPacketBuffer);
  udpSend.endPacket();
  udpSend.flush();
  dbg("Sent %s", msg);
}

boolean receive(char* buffer, int bufferSize) {
   int packetSize = udpReceive.parsePacket();
   if(packetSize > 0) {
       memset(buffer, 0, bufferSize);
       udpReceive.read(buffer, bufferSize);
       udpReceive.flush();
       return true;
     }
     return false;
}
