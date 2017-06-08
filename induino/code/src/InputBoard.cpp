

#include "InputBoard.h"
#include "mcp.h"
#include "Arduino.h"

InputBoard::InputBoard(int address) {
    mcp.begin(address);
    for(int i = 0; i < 16; i++) {
      mcp.pinMode(i, INPUT);
      mcp.pullUp(i, 1);
    }
}
