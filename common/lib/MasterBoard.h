

#ifndef _MASTERBOARD_H_
#define _MASTERBOARD_H_

#include "Timer.h"

class MasterBoard {
  private:
    int okLedPin;
    int errorLedPin;
    int id;
    Timer blueLedTimer;

  public:
    MasterBoard(int okLedPin, int errorLedPin);
    /// get board ID from dip switch
    int getId();

    /// call this periodically from main loop
    void loop();

    void blinkOkLed(int time);
    void setErrorLed(bool value);


};


#endif
