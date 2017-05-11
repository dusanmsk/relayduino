

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

#include <avr/io.h>
//#include <avr/wdt.h>

#include "Network.h"


Board board(LED_PIN, CONFIG_BUTTON_PIN);
Configuration cfg;
OutputPorts outputPorts;
Serial595 s595(DATA_PIN, OE_PIN, RCLK_PIN, SRCLK_PIN);

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
  s595.setOutputEnable(false);
  board.initialize();
  board.blinkBoardId();
}


void setup() {

  Serial.begin(BAUDRATE);
  delay(2000);    // do initial sleep (give user time to move finger from reset to config button)
  dbg("Started");

  initialize();

  outputPorts.setOn(1);
  outputPorts.setOn(8);
  outputPorts.setOn(15);
  outputPorts.setOn(22);
  outputPorts.setOn(29);


}





void loop() {
  shiftRelays();
  delay(1000000);
}
