
#include "OutputPorts.h"
#include "dbg.h"


void OutputPorts::setPort(int port, int value) {
  if(port >= 0 && port < NUM_OF_PORTS) {
    value = (value == 0 ? 0 : (1 + timeoutCount));
    ports[port] = value;
  }
}

int OutputPorts::getValue(int port){
  if(port >= 0 && port < NUM_OF_PORTS) {
    return ports[port];
  }
  return -1;
}

int OutputPorts::processTimeouts() {
  int timedOut = 0;
  if(timeoutCount == 0) { return 0; }
  for(int port = 0; port < NUM_OF_PORTS; port++) {
    int value = ports[port];
    if(value > 0) {
      ports[port] = --value;
      if(value == 0) {
        timedOut++;
      }
    }
  }
  return timedOut;
}

void OutputPorts::printDebugInfo() {
  for(int i = 0; i < NUM_OF_PORTS; i++) {
    int value = ports[i];
    dbg("Port %d : %d", i, value);
  }

}
