

#include "MasterBoard.h"
#include <Arduino.h>
#include "Globals.h"
#include "dbg.h"

/*
  TODO:
  dip switch pins: TODO do not conflict with SPI !!!
  led pins: 36 (red), 28 (blue)
*/

MasterBoard::MasterBoard() {
  // TODO read address dip switch
  pinMode(INFO_LED_PIN, OUTPUT);
  digitalWrite(INFO_LED_PIN, LOW);
  pinMode(ERROR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_LED_PIN, LOW);

  id = 0;

}

int MasterBoard::getId() {
  return id;
}

void MasterBoard::setErrorLed(bool value) {
  digitalWrite(ERROR_LED_PIN, value ? HIGH : LOW);
}


void MasterBoard::blinkInfoLed(int timeMs) {
  digitalWrite(INFO_LED_PIN, HIGH);
  blueLedTimer.sleep(timeMs);
}

void MasterBoard::loop() {

  if(blueLedTimer.isOver()) {
    digitalWrite(INFO_LED_PIN, LOW);
  }


}
