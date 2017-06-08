

#ifndef _INPUT_BOARD_H
#define _INPUT_BOARD_H

#include "mcp.h"

class InputBoard {
private:

public:
  Adafruit_MCP23017 mcp;
  InputBoard(int address);
};


#endif
