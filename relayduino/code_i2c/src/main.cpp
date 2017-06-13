
#define NETWORK 192, 168, 100
#define MASK 255,255,255,0

#include "Globals.h"
#include "MainBoard.h"
#include "dbg.h"
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "mcp.h"
#include "RelayBoard.h"
#include "Timer.h"

/*
  TODO:
  - setup main board (casom)
  - find all relayboards
  - receive tcp command
    - set relays
    - process timeouts
*/

MainBoard mainBoard;
EthernetServer server(5000);
Timer redLedTimer;

#define NUM_OF_RELAY_BOARDS 8
RelayBoard* relayBoards[NUM_OF_RELAY_BOARDS] = {
    new RelayBoard(0),
    new RelayBoard(1),
    new RelayBoard(2),
    new RelayBoard(3),
    new RelayBoard(4),
    new RelayBoard(5),
    new RelayBoard(6),
    new RelayBoard(7)
};

byte mac[6] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xA0 };
byte ip[4] = {NETWORK, 180};
byte mask[4] = { MASK };

void setup() {

  Serial.begin(115200);
  while (!Serial);

  int mainBoardId = mainBoard.getId();
  dbg("Main board id: %d", mainBoardId);

  mask[3]+=mainBoardId;
  ip[3]+=mainBoardId;
  Ethernet.begin(mac, ip, mask);
  server.begin();

  dbg("Assigned address: %d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

  // initialize relay boards
  for(int i = 0; i < NUM_OF_RELAY_BOARDS; i++) {
    RelayBoard* relayBoard =  relayBoards[i];
    relayBoard->initialize();
  }
}


#define recvBufferSize 2048
char recvBuffer[recvBufferSize];
bool alreadyConnected;
int relayBoardId, relayId, relayValue, parsedArgs;
Timer relaysTimeoutTimer;

void loop4() {
  EthernetClient client = server.available();
  if (client) {
      if (!alreadyConnected) {
        // clear out the input buffer:
        client.flush();
        alreadyConnected = true;
      }

      while (client.available()) {
        String cmd = client.readStringUntil(';');
        dbg("%s", cmd.c_str());
        Serial.println("");
      }
    }
}

void loop() {

  EthernetClient client = server.available();

  if (client) {
      if (!alreadyConnected) {
        // clear out the input buffer:
        client.flush();
        alreadyConnected = true;
      }

      while (client.available()) {
        //int how = client.read(recvBuffer, recvBufferSize-1);
        //recvBuffer[how] = '\0';
        //String cmd = String((const char*)&recvBuffer);
        String cmd = client.readStringUntil(';');
        dbg("%s", cmd.c_str());
        mainBoard.blinkBlueLed(100);
        redLedTimer.sleep(60000); // TODO nastavit na timeout - pokym nepride v dany cas ziaden packet - rozsviet red led
        mainBoard.setRedLed(false);

        parsedArgs = sscanf(cmd.c_str(), "b%d r%d %d", &relayBoardId ,&relayId, &relayValue);
        if(parsedArgs == 3) {
          RelayBoard* relayBoard = relayBoards[relayBoardId];
          relayBoard->setRelay(relayId, relayValue);
          relayBoard->sendData();

        }
      }
    }

    // process timeouts in intervals
    if(relaysTimeoutTimer.isOver()) {
      for(int i = 0; i < NUM_OF_RELAY_BOARDS; i++) {
        RelayBoard* relayBoard = relayBoards[i];
        if(relayBoard->processTimeouts()) {
          relayBoard->sendData();
        }
      }
      relaysTimeoutTimer.sleep(1000);
    }


    mainBoard.loop();
    if(redLedTimer.isOver()) {
      mainBoard.setRedLed(true);
    }



}
