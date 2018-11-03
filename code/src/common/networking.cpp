
#include "networking.h"
#include "dbg.h"

byte mac[6] = {  0xDE, 0xAD, 0xBE, 0xAA, 0xFE, 0x01 };
byte ip[4] = { NETWORK, 0 };
byte mask[4] = { MASK };

EthernetUDP udp;

void initNetwork(int addressOffset) {
  mac[5] += addressOffset;
  ip[3]+=addressOffset;
  Ethernet.begin(mac, ip, mask);
  udp.begin(LISTEN_PORT);

  dbg("Assigned address: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

}

void send(char* msg) {
  dbg("Sending %s", msg)
  udp.beginPacket(SEND_IP_ADDRESS, LOXONE_PORT);
  udp.print(msg);
  udp.endPacket();
  dbg("Sent %s", msg);
}

bool receiveMessage(char* buffer, int bufferSize) {
   int packetSize = udp.parsePacket();
   if(packetSize > 0) {
       memset(buffer, 0, bufferSize);
       udp.readBytesUntil(';', buffer,bufferSize);
        udp.flush();
        return true;
       }
     
     return false;
}
