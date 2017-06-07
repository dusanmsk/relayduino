
#ifndef _TIMER_H_
#define _TIMER_H_

#include "Arduino.h"

class Timer {
  private:
    unsigned long timestampLastHitMs;
    unsigned long sleepTimeMs;
  public:
    bool isOver() {
      if (millis() - timestampLastHitMs < sleepTimeMs) {
          return false;
      }
      timestampLastHitMs = millis();
      return true;
    }
    void sleep(unsigned long sleepTimeMs) {
      this->sleepTimeMs = sleepTimeMs;
      timestampLastHitMs = millis();
    }
};



#endif
