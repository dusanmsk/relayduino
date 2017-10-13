/**
  With UDP syntax of commands changed a bit, because it must contain master board id.

  Example command:
  m1 b2 r3 1

  Means:
  Set master board 1 -> slave board 2 -> relay 3 -> on

*/


#define LOCAL_PORT 6666
#define PING_TIMEOUT_MS 15000

// TODO make ifdef mega/nanoatmega328
#define OK_LED_PIN 28
#define ERROR_LED_PIN 36

// TODO nano set proper pins
//#define OK_LED_PIN 14
//#define ERROR_LED_PIN 14

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
  - receive commands as udp broadcasts
  - receive and response on ping commands by udp broadcasts
*/

MainBoard mainBoard(OK_LED_PIN, ERROR_LED_PIN);
Timer pingTimer;
EthernetUDP ethernetUdp;

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

byte mac[6] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x30};
char mainBoardIdStr[4];
int mainBoardIdStrLen;

void(* uglyResetTheBoard) (void) = 0; //declare reset function @ address 0 - ugly hard hack that works
int failedPings = 0;

void setup() {
  Serial.begin(115200);

  int mainBoardId = mainBoard.getId();
  snprintf(mainBoardIdStr, 4, "m%d", mainBoardId);
  mainBoardIdStrLen = strlen(mainBoardIdStr);
  dbg("Main board id: %d", mainBoardId);
  dbg("Main board id string: %s", mainBoardIdStr);

  mac[5] += mainBoardId;
  Ethernet.begin(mac);
  ethernetUdp.begin(LOCAL_PORT);

  // initialize relay boards
  for(int i = 0; i < NUM_OF_RELAY_BOARDS; i++) {
    RelayBoard* relayBoard =  relayBoards[i];
    relayBoard->initialize();
  }
  pingTimer.sleep(PING_TIMEOUT_MS);
}


#define recvBufferSize UDP_TX_PACKET_MAX_SIZE
char recvBuffer[recvBufferSize];
bool alreadyConnected;
int relayBoardId, relayId, relayValue, parsedArgs, ignoredMasterBoardId;
boolean isOnline;

void loop() {
  int packetSize = ethernetUdp.parsePacket();
  if(packetSize > 0) {
      memset(recvBuffer, 0, recvBufferSize);
      ethernetUdp.read(recvBuffer, recvBufferSize);
      ethernetUdp.flush();
      //dbg("Received %s", recvBuffer)

      // process ping command
      if(strncmp(recvBuffer, "ping", recvBufferSize) == 0) {
        isOnline = true;
        pingTimer.sleep(PING_TIMEOUT_MS);
        mainBoard.blinkOkLed(30);
        mainBoard.setErrorLed(false);
        // TODO send pong
        dbgn("Ping processed");
      }

      // if it was not ping command, check if command is for this masterboard
      else if (strncmp(recvBuffer, mainBoardIdStr, mainBoardIdStrLen ) == 0) {
        parsedArgs = sscanf(recvBuffer, "m%d b%d r%d %d", &ignoredMasterBoardId, &relayBoardId ,&relayId, &relayValue);
        if(parsedArgs == 4) {
          pingTimer.sleep(PING_TIMEOUT_MS);
          mainBoard.blinkOkLed(30);
          mainBoard.setErrorLed(false);
          relayId--;
          RelayBoard* relayBoard = relayBoards[relayBoardId];
          relayBoard->setRelay(relayId, relayValue);
          relayBoard->sendData();
          dbg("Relay %d/%d set to %d", relayBoardId, relayId, relayValue)
        } else {
          dbgn("Invalid number of arguments");
          mainBoard.setErrorLed(true);
        }
      }
  }

  // process ping timeout - possible connection lost - turn everything off immediately
  if(pingTimer.isOver()) {
    dbgn("No ping - connection lost? Turning everything off");
    isOnline = false;
    for(int i = 0; i < NUM_OF_RELAY_BOARDS; i++) {
      RelayBoard* relayBoard = relayBoards[i];
      for(int r = 0; r < 16; r++) {
        relayBoard->setRelay(r, 0);
      }
      relayBoard->sendData();
    }
    pingTimer.sleep(PING_TIMEOUT_MS);
    mainBoard.setErrorLed(true);
    if(failedPings++ > 10) {
      dbgn("No ping for a long time, trying to reset the device");
      delay(5000);
      uglyResetTheBoard();
    }

  }

  mainBoard.loop();

}
