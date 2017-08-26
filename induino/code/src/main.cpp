
#define NETWORK 192, 168, 100
#define MASK 255,255,255,0
#define LOCAL_PORT 5556
#define LOXONE_PORT 5555
#define SEND_IP_ADDRESS "255.255.255.255"

#define outputPacketBufferSize 128


#include "MainBoard.h"
#include "dbg.h"
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "mcp.h"
#include "Globals.h"
#include "InputBoard.h"
//#include "Timer.h"

/*
  TODO:
  - setup main board (casom)
  - find all input boards
*/

MainBoard mainBoard;

byte mac[6] = {  0xDE, 0xAD, 0xBE, 0xAA, 0xFE, 0xA0 };
byte ip[4] = { NETWORK, 120 };
byte mask[4] = { MASK };

EthernetUDP udpSend;
char outputPacketBuffer[outputPacketBufferSize];

#define NUM_OF_INPUT_BOARDS 8

InputBoard* connectedBoards[NUM_OF_INPUT_BOARDS];
Adafruit_MCP23017 mcp;

void setup() {

  Serial.begin(115200);
  while (!Serial);

  int mainBoardId = mainBoard.getId();
  dbg("Main board id: %d", mainBoardId);

  mask[3]+=mainBoardId;
  ip[3]+=mainBoardId;
  Ethernet.begin(mac, ip, mask);
  udpSend.begin(LOCAL_PORT);

  //server.begin();

  dbg("Assigned address: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

  // find input boards
  int error;
  Wire.begin();
  for(int adr = 0; adr < NUM_OF_INPUT_BOARDS; adr++) {
    connectedBoards[adr] = 0;
    Wire.beginTransmission(adr + MCP23017_ADDRESS);
    error = Wire.endTransmission();
    if (error == 0) {
      dbg("Found input board at address: %d", adr);
      connectedBoards[adr] = new InputBoard(&mcp, adr);
    }
  }

}


void sendCommand(int mainBoardId, int inputBoardId, int inputId, int value) {
  snprintf(outputPacketBuffer, outputPacketBufferSize, "m%d b%d i%d %d", mainBoardId, inputBoardId, inputId+1, value);
  dbg("Sending %s", outputPacketBuffer);
  udpSend.beginPacket(SEND_IP_ADDRESS, LOXONE_PORT);
  udpSend.write(outputPacketBuffer);
  udpSend.endPacket();
}

void loop() {

  // iterate over all connected boards
  for(int address = 0; address < NUM_OF_INPUT_BOARDS; address++) {
    if(connectedBoards[address]) {
      InputBoard* inputBoard = connectedBoards[address];
      int responses[16];
      inputBoard->readInputs(responses);
      for(int i = 0; i < 16; i++) {
        if(responses[i] != 0 ) {
          sendCommand(mainBoard.getId(), inputBoard->getId(), i,  responses[i] == -1 ? 0 : 1);
        }
      }
    }
  }
}
