

#ifndef _MAINBOARD_H_
#define _MAINBOARD_H_

#include "Timer.h"

class MainBoard {
  private:
    int okLedPin;
    int errorLedPin;
    int id;
    Timer blueLedTimer;

  public:
    MainBoard(int okLedPin, int errorLedPin);
    /// get board ID from dip switch
    int getId();

    /// call this periodically from main loop
    void loop();

    void blinkOkLed(int time);
    void setErrorLed(bool value);


};


#endif
