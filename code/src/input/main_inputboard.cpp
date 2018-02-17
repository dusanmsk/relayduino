
#include "../common/Globals.h"
#include "../common/MasterBoard.h"
#include "../common/dbg.h"
#include "InputBoard.h"
#include "../common/networking.h"

#include <SPI.h>
#include <Wire.h>
#include "../common/mcp.h"

//#include "Timer.h"


/*
  TODO:
  - setup main board (casom)
  - find all input boards
*/

char recvBuffer[recvBufferSize];

MasterBoard masterBoard;
Timer pingTimer;

char masterBoardIdStr[5];
int masterBoardIdStrLen;

#define NUM_OF_INPUT_BOARDS 8

InputBoard* connectedBoards[NUM_OF_INPUT_BOARDS];
Adafruit_MCP23017 mcp;

void(* uglyResetTheBoard) (void) = 0; //declare reset function @ address 0 - ugly hard hack that works

void setup() {

  Serial.begin(9600);
  //while (!Serial);

  int masterBoardId = masterBoard.getId();
  snprintf(masterBoardIdStr, 5, "im%d", masterBoardId);
  masterBoardIdStrLen = strlen(masterBoardIdStr);

  dbg("Master board id: %s", masterBoardIdStr);

  // input masterBoards starts 192.168.100.120
  initNetwork(120 + masterBoardId);

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

  bool blink = true;
  for(int i = 0; i < 10; i++) {
	  masterBoard.setInfoLed(blink);
	  masterBoard.setErrorLed(!blink);
    blink = !blink;
	  delay(50);
  }
	masterBoard.setInfoLed(false);
	masterBoard.setErrorLed(false);

  // TODO send hello {boardid} to network

}


void sendCommand(int masterBoardId, int inputBoardId, int inputId, int value) {
  char buf[32];
  snprintf(buf, 32, "im%d b%d i%d %d", masterBoardId, inputBoardId, inputId+1, value);
  dbg("Sending %s", buf);
  send(buf);
}

boolean isOnline;
int failedPings = 0;

void loop() {

  // iterate over all connected boards
  for(int address = 0; address < NUM_OF_INPUT_BOARDS; address++) {
    if(connectedBoards[address]) {
      InputBoard* inputBoard = connectedBoards[address];
      int responses[16];
      inputBoard->readInputs(responses);
      for(int i = 0; i < 16; i++) {
        if(responses[i] != 0 ) {
            masterBoard.blinkInfoLed(30);
          sendCommand(masterBoard.getId(), inputBoard->getId(), i,  responses[i] == -1 ? 0 : 1);
        }
      }
    }
  }

  // process ping
  if(receive(recvBuffer, recvBufferSize)) {
      //dbg("Received %s", recvBuffer)

      // process ping command
      if(strncmp(recvBuffer, "ping", recvBufferSize) == 0) {
        isOnline = true;
        pingTimer.sleep(PING_TIMEOUT_MS);
        masterBoard.blinkInfoLed(30);
        masterBoard.setErrorLed(false);
        char buf[32];
        snprintf(buf, 32, "%s pong", masterBoardIdStr);
        send(buf);
      }
  }

  // process ping timeout - possible connection lost - turn everything off immediately
  if(pingTimer.isOver()) {
    dbgn("No ping - connection lost?");
    isOnline = false;
    pingTimer.sleep(PING_TIMEOUT_MS);
    masterBoard.setErrorLed(true);
    if(failedPings++ > 10) {
      dbgn("No ping for a long time, trying to reset the device");
      delay(5000);
      uglyResetTheBoard();
    }
  }

  masterBoard.loop();
}
