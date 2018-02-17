

#include "RelayBoard.h"

RelayBoard::RelayBoard(int id) { this->id = id; }

void RelayBoard::initialize() {
  mcp.begin(id);
  for(int u = 0; u < 16; u++) {
    mcp.pinMode(u, OUTPUT);
    mcp.digitalWrite(u, LOW);
  }
}

void RelayBoard::setRelay(int relayId, int value) {
  ports.setPort(relayId, value);
}

void RelayBoard::sendData() {
  for(int u = 0; u < 16; u++) {
    mcp.digitalWrite(u, ports.getValue(u));
  }
}

int  RelayBoard::processTimeouts() {
  return ports.processTimeouts() ;
}
