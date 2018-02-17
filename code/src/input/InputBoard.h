

#ifndef _INPUT_BOARD_H
#define _INPUT_BOARD_H

#include "../common/mcp.h"

class InputBoard {
private:
  Adafruit_MCP23017* mcp;
  int address;
  int counters[16];
  bool inputs[16];

public:
  InputBoard(Adafruit_MCP23017* mcp, int address);
  void readInputs(int responses[]);
  int getId() { return address; }
};


#endif
