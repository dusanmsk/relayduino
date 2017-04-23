
#ifndef _OUTPUT_PORTS_H
#define _OUTPUT_PORTS_H

#include "595.h"

static const int NUM_OF_PORTS = 8 * 7;

// TODO rename to "OutputPorts"
class OutputPorts {
private:
  int ports[NUM_OF_PORTS+1];
  int timeoutCount;
public:

  OutputPorts() {
    ::OutputPorts(0);
  }

  /**
      Arguments:
      timeoutCount - 0 to disable, n>0 to enable and set the value
  */
  OutputPorts(int timeoutCount) {
    if(timeoutCount < 0) { timeoutCount = 0; }
    this->timeoutCount = timeoutCount;
    for(int i = 1; i <= NUM_OF_PORTS; i++ ) {
      ports[i] = 0;
    }
  }
  int setOn(int port);
  int setOff(int port);
  bool getValue(int port);

  /**
    If running in timeout mode, you should call this method periodically.
    Each call finds and sets off all ports that was not set on for a specified number of calls of this method (see argument in constructor).
    Returns number of timeouted ports.
  */
  int processTimeouts();
};




#endif
