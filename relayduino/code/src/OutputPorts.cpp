
#include "OutputPorts.h"
#include "dbg.h"


int OutputPorts::setOn(int port) {
    if(port > 0 && port < NUM_OF_PORTS) {
      ports[port] = 1 + timeoutCount;
      return 0;
    }
    return -1;
}

int OutputPorts::setOff(int port) {
    if(port > 0 && port < NUM_OF_PORTS) {
      ports[port] = 0;
      return 0;
    }
    return -1;
}

bool OutputPorts::getValue(int port){
  if(port > 0 && port < NUM_OF_PORTS) {
    return ports[port] > 0;
  }
  return false;
}

int OutputPorts::processTimeouts() {
  int timedOut = 0;
  if(timeoutCount == 0) { return 0; }
  for(int i = 0; i < NUM_OF_PORTS; i++) {
    int value = ports[i];
    if(value > 0) {
      ports[i] = --value;
      if(value == 0) {
        timedOut++;
      }
    }
  }
  return timedOut;
}
