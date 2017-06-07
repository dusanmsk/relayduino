

#ifndef _MAINBOARD_H_
#define _MAINBOARD_H_

#include "Timer.h"

class MainBoard {
  private:
    int id;
    Timer blueLedTimer;

  public:
    MainBoard();
    /// get board ID from dip switch
    int getId();

    /// call this periodically from main loop
    void loop();

    void blinkBlueLed(int time);


};


#endif
