/**
  TODO doc
**/

#ifndef _OUTPUT_PORTS_H
#define _OUTPUT_PORTS_H

static const int NUM_OF_PORTS = 16;

class OutputPorts {
private:
  int timeoutCount;
  int ports[NUM_OF_PORTS+1];
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
    for(int i = 0; i <= NUM_OF_PORTS; i++ ) {
      ports[i] = 0;
    }
  }

  void setPort(int port, int value);
  int getValue(int port);

  /**
   TODO deprecated, remove
    If running in timeout mode, you should call this method periodically.
    Each call finds and sets off all ports that was not set on for a specified number of calls of this method (see argument in constructor).
    Returns number of timeouted ports.
  */
  int processTimeouts();

  void printDebugInfo();
};




#endif
