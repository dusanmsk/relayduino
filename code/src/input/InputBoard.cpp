

#include "InputBoard.h"
#include "../common/mcp.h"
#include "Arduino.h"
#include "../common/dbg.h"

int samples = 4;

InputBoard::InputBoard(  Adafruit_MCP23017* mcp, int address) {
    this->mcp = mcp;
    this->address = address;
    mcp->begin(address);
    for(int i = 0; i < 16; i++) {
      mcp->pinMode(i, INPUT);
      mcp->pullUp(i, 1);
      counters[i] = 0;
      inputs[i] = false;
    }
}

void InputBoard::readInputs(int responses[]) {
  mcp->begin(address);
  uint16_t ab = mcp->readGPIOAB();
  for(int i = 0; i < 16; i++) {
    responses[i] = 0;
    int counter = counters[i];
    boolean status = inputs[i];
    if(ab & 1) {
      counter--;
    } else {
      counter++;
    }
    if(counter > samples) {
      counter = samples;
      if(!status) {
        inputs[i] = true;
        responses[i] = 1;
      }
    }
    if(counter < -samples) {
      counter = -samples;
      if(status) {
        inputs[i] = false;
        responses[i] = -1;
      }
    }
    counters[i] = counter;
    ab>>=1;
  }
}
