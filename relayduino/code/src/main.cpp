
#define DATA_PIN  2
#define OE_PIN 3
#define RCLK_PIN  4
#define SRCLK_PIN  5
#define CONFIG_BUTTON_PIN 7
#define LED_PIN A5    // TODO move to A7
#define BAUDRATE 115200

#include "Arduino.h"
#include "Board.h"
#include "main.h"
#include "dbg.h"
#include "Configuration.h"
#include "EEPROM.h"
#include "Network.h"
#include "OutputPorts.h"
#include "595.h"
#include "Timer.h"

#include <avr/io.h>
//#include <avr/wdt.h>

#include "Network.h"


byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0};
const int listenPort = 5555;


Board board(LED_PIN, CONFIG_BUTTON_PIN);
Configuration cfg;
OutputPorts outputPorts(10);
Serial595 s595(DATA_PIN, OE_PIN, RCLK_PIN, SRCLK_PIN);
Network network;

void shiftRelays() {
  int portIndex = 56;
  for(int i = 0; i < 8; i++) {
    for(int u = 0; u < 7; u++) {
      bool value = outputPorts.getValue(portIndex--);
      s595.writeBit(value);
    }
    s595.writeBit(false);  // bit 8 of each shift register is not used/connected
  }

  s595.propagateData();
  s595.setOutputEnable(true);
}


void initialize() {

  // initialize board
  s595.setOutputEnable(false);
  board.initialize();
  board.blinkBoardId();

  // initialize network
  mac[5] = (0xED + board.getBoardId());
  IPAddress listenIpAddress = IPAddress(192, 168, 150, 150 + board.getBoardId());
  network.begin(mac, listenIpAddress);
}


void setup() {

  Serial.begin(BAUDRATE);
  delay(2000);    // do initial sleep (give user time to move finger from reset to config button)
  dbg("Start");

  initialize();

  dbg("Initialized");
}



Timer relaysTimeoutTimer;
int boardId, relayId, relayValue, parsedArgs;
void loop() {

  // receive packet
  if(network.receiveUdp(listenPort)) {
    String packet = network.getReceivedPacket();
    //dbg(packet);
    parsedArgs = sscanf(packet.c_str(), "b%d r%d %d", &boardId ,&relayId, &relayValue);
    if(parsedArgs == 3 && boardId == board.getBoardId()) {
        if(relayValue > 0) {
          outputPorts.setOn(relayId);
        } else {
          outputPorts.setOff(relayId);
        }
        shiftRelays();
      }
    }

    // TODO process this only when in "timeout" mode
    // process relay timeouts
    if(relaysTimeoutTimer.isOver()) {
      int howTimeout = outputPorts.processTimeouts();
      dbg(howTimeout);
      if(howTimeout > 0) {
        shiftRelays();
      }
      relaysTimeoutTimer.sleep(1000);
    }


}
