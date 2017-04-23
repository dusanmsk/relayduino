
#ifndef _RELAYS_H
#define _RELAYS_H

#include "595.h"

#define RELAY_ON_TIMEOUT 10

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
  int relayOn(int relay);
  int relayOff(int relay);
  bool getRelay(int relay);
};




#endif
