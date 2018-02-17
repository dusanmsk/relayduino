

#include "MasterBoard.h"
#include <Arduino.h>
#include "Globals.h"
#include "dbg.h"

MasterBoard::MasterBoard() {
  #ifdef __AVR_ATmega328P__
	  //read address dip switch
	  pinMode(DIP_PIN1, INPUT_PULLUP);
	  pinMode(DIP_PIN2, INPUT_PULLUP);
	  pinMode(DIP_PIN3, INPUT_PULLUP);
	  pinMode(DIP_PIN4, INPUT_PULLUP);
	  if (!digitalRead(DIP_PIN1)) { this->id |= 1; }
	  if (!digitalRead(DIP_PIN2)) { this->id |= 2; }
	  if (!digitalRead(DIP_PIN3)) { this->id |= 4; }
	  if (!digitalRead(DIP_PIN4)) { this->id |= 8; }
  #endif
  pinMode(INFO_LED_PIN, OUTPUT);
  digitalWrite(INFO_LED_PIN, LOW);
  pinMode(ERROR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_LED_PIN, LOW);

}

int MasterBoard::getId() {
  return id;
}

void MasterBoard::setErrorLed(bool value) {
  digitalWrite(ERROR_LED_PIN, value ? HIGH : LOW);
}

void MasterBoard::setInfoLed(bool value) {
  digitalWrite(INFO_LED_PIN, value ? HIGH : LOW);
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
