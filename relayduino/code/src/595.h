
#ifndef _595_H
#define _595_H

#include "arduino.h"

#include "dbg.h"

class Serial595 {
private:
  int dataPin, oePin, rclkPin, srclkPin;
public:
  Serial595(int dataPin, int oePin, int rclkPin, int srclkPin) {
    this->dataPin = dataPin;
    this->oePin = oePin;
    this->rclkPin = rclkPin;
    this->srclkPin = srclkPin;
    pinMode(dataPin, OUTPUT);
    pinMode(oePin, OUTPUT);
    pinMode(rclkPin, OUTPUT);
    pinMode(srclkPin, OUTPUT);
    digitalWrite(oePin, HIGH);
    digitalWrite(dataPin, LOW);
    digitalWrite(rclkPin, LOW);
    digitalWrite(srclkPin, LOW);
  }

  /*
    Shift single bit to registers
  */
  void writeBit(bool value) {
      dbg("Pica");
      digitalWrite(dataPin, value ? HIGH : LOW);
      digitalWrite(srclkPin, HIGH);
      //delay(10);
      digitalWrite(srclkPin, LOW);
  }

  /*
    Enable/disable outputs
  */
  void setOutputEnable(bool enable) {
    dbgf("Enable output: %s", enable ? "true" : "false");
    digitalWrite(oePin, enable ? LOW : HIGH);
  }

  /*
    Propagate data from serial registers to outputs.
  */
  void propagateData() {
    digitalWrite(rclkPin, HIGH);
    digitalWrite(rclkPin, LOW);
  }

};

#endif
