
#include "Relays.h"
#include "dbg.h"


int Relays::setRelay(int relay, int status) {
    if(relay > 0 && relay < NUM_OF_RELAYS) {
      dbgf2("Setting relay %d to %d", relay, status);
      relays[relay] = status;
      return 0;
    }
    return -1;
}

int Relays::getRelay(int relay){
  if(relay > 0 && relay < NUM_OF_RELAYS) {
    return relays[relay];
  }
  return -1;
}
