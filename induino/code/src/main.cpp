
#define NETWORK 192, 168, 100
#define MASK 255,255,255,0


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
byte ip[4] = {NETWORK, 120};
byte mask[4] = { MASK };


#define NUM_OF_INPUT_BOARDS 8

int connectedBoards[NUM_OF_INPUT_BOARDS];


void setup() {

  Serial.begin(115200);
  while (!Serial);

  int mainBoardId = mainBoard.getId();
  dbgf("Main board id: %d", mainBoardId);

  mask[3]+=mainBoardId;
  ip[3]+=mainBoardId;
  //Ethernet.begin(mac, ip, mask);
  //server.begin();

  dbgf4("Assigned address: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

  // find input boards
  int error;
  Wire.begin();
  for(int adr = 0; adr < NUM_OF_INPUT_BOARDS; adr++) {
    connectedBoards[adr] = 0;
    Wire.beginTransmission(adr + MCP23017_ADDRESS);
    error = Wire.endTransmission();
    if (error == 0) {
      dbgf("Found input board at address: %d", adr);
      connectedBoards[adr] = 1;
    }
  }

}

Adafruit_MCP23017 mcp;
void loop() {

  // iterate over all connected boards
  for(int address = 0; address < NUM_OF_INPUT_BOARDS; address++) {
    if(connectedBoards[address]) {
      mcp.begin(address);
      uint16_t x = mcp.readGPIOAB();
      x = ~x;
      String s  = String(x, BIN);
      dbgf2("read from %d: %s", address, s.c_str());
    }
  }

  delay(200);

}
