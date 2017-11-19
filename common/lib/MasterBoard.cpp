

#include "MasterBoard.h"
#include <Arduino.h>
#include "Globals.h"
#include "dbg.h"

/*
  TODO:
  dip switch pins: 52,50,48,46
  led pins: 36 (red), 28 (blue)
*/

MasterBoard::MasterBoard(int okLedPin, int errorLedPin) {
  this->okLedPin = okLedPin;
  this->errorLedPin = errorLedPin;
  // TODO read address dip switch
  pinMode(okLedPin, OUTPUT);
  digitalWrite(okLedPin, LOW);
  pinMode(errorLedPin, OUTPUT);
  digitalWrite(errorLedPin, LOW);

  id = 0;

}

int MasterBoard::getId() {
  return id;
}

void MasterBoard::setErrorLed(bool value) {
  digitalWrite(errorLedPin, value ? HIGH : LOW);
}


void MasterBoard::blinkOkLed(int timeMs) {
  digitalWrite(okLedPin, HIGH);
  blueLedTimer.sleep(timeMs);
}

void MasterBoard::loop() {

  if(blueLedTimer.isOver()) {
    digitalWrite(okLedPin, LOW);
  }


}
