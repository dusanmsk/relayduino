
#ifndef _RELAYS_H
#define _RELAYS_H

#include "595.h"

static const int NUM_OF_RELAYS = 8 * 7;

class Relays {
private:
  int relays[NUM_OF_RELAYS+1];
public:
  Relays() {
    for(int i = 1; i <= NUM_OF_RELAYS; i++ ) {
      relays[i] = 0;
    }
  }
  int setRelay(int relay, int status);
  int getRelay(int relay);
};




#endif
