

#ifndef _RELAYBOARD_H_
#define _RELAYBOARD_H_

#include "OutputPorts.h"
#include "Globals.h"
#include "mcp.h"
#include "Arduino.h"
#include "dbg.h"

class RelayBoard {

  private:
    int id;
    Adafruit_MCP23017 mcp;


  public:
    OutputPorts ports = OutputPorts(OUTPUT_PORTS_TIMEOUT);
    RelayBoard(int id);
    void initialize();
    void setRelay(int relayId, int value);
    void sendData();
    int  processTimeouts();
};


#endif
