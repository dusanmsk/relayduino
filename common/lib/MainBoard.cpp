

#include "MainBoard.h"
#include <Arduino.h>
#include "Globals.h"
#include "dbg.h"

/*
  TODO:
  dip switch pins: 52,50,48,46
  led pins: 36 (red), 28 (blue)
*/

MainBoard::MainBoard(int okLedPin, int errorLedPin) {
  this->okLedPin = okLedPin;
  this->errorLedPin = errorLedPin;
  // TODO read address dip switch
  pinMode(okLedPin, OUTPUT);
  digitalWrite(okLedPin, LOW);
  pinMode(errorLedPin, OUTPUT);
  digitalWrite(errorLedPin, LOW);

  id = 0;

}

int MainBoard::getId() {
  return id;
}

void MainBoard::setErrorLed(bool value) {
  digitalWrite(errorLedPin, value ? HIGH : LOW);
}


void MainBoard::blinkOkLed(int timeMs) {
  digitalWrite(okLedPin, HIGH);
  blueLedTimer.sleep(timeMs);
}

void MainBoard::loop() {

  if(blueLedTimer.isOver()) {
    digitalWrite(okLedPin, LOW);
  }


}
