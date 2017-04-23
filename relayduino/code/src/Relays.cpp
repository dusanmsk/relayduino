
#include "Relays.h"
#include "dbg.h"


int Relays::relayOn(int relay) {
    if(relay > 0 && relay < NUM_OF_RELAYS) {
      relays[relay] = RELAY_ON_TIMEOUT;
      return 0;
    }
    return -1;
}

int Relays::relayOff(int relay) {
    if(relay > 0 && relay < NUM_OF_RELAYS) {
      relays[relay] = 0;
      return 0;
    }
    return -1;
}

bool Relays::getRelay(int relay){
  if(relay > 0 && relay < NUM_OF_RELAYS) {
    return relays[relay] > 0;
  }
  return false;
}
