

#include "MainBoard.h"
#include "Arduino.h"
#include "Globals.h"

/*
  TODO:
  dip switch pins: 52,50,48,46
  led pins: 36 (red), 28 (blue)
*/

MainBoard::MainBoard() {
  // TODO read address dip switch
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, LOW);
  pinMode(RED_LED_PIN, OUTPUT);
  digitalWrite(RED_LED_PIN, LOW);

  pinMode(DIP_PIN1, INPUT_PULLUP);
  pinMode(DIP_PIN2, INPUT_PULLUP);
  pinMode(DIP_PIN3, INPUT_PULLUP);
  id = 0;
  // !!!!!! TODO uncomment when shield will be reviewed
  //if (digitalRead(DIP_PIN1) == LOW) { id |= 1; }
  //if (digitalRead(DIP_PIN2) == LOW) { id |= 2; }
  //if (digitalRead(DIP_PIN3) == LOW) { id |= 4; }

}

int MainBoard::getId() {
  return id;
}

void MainBoard::setRedLed(bool value) {
  digitalWrite(RED_LED_PIN, value ? HIGH : LOW);
}


void MainBoard::blinkBlueLed(int timeMs) {
  digitalWrite(BLUE_LED_PIN, HIGH);
  blueLedTimer.sleep(timeMs);
}

void MainBoard::loop() {

  if(blueLedTimer.isOver()) {
    digitalWrite(BLUE_LED_PIN, LOW);
  }


}
