

#ifndef _MASTERBOARD_H_
#define _MASTERBOARD_H_

#include "Timer.h"

class MasterBoard {
  private:
    int okLedPin;
    int errorLedPin;
    int id = 0;
    Timer blueLedTimer;

  public:
    MasterBoard();
    /// get board ID from dip switch
    int getId();

    /// call this periodically from main loop
    void loop();

    void initBlink();
    void blinkInfoLed(int time);
    void setInfoLed(bool value);
    void setErrorLed(bool value);


};


#endif
