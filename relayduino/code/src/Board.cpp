
#include "Arduino.h"
#include "Board.h"
#include "dbg.h"
#include "Network.h"
#include "EEPROM.h"

#define EEPROM_BOARD_ID_OFFSET 0


Board::Board(int ledPin, int configButtonPin) {
  this->configButtonPin = configButtonPin;
  this->ledPin = ledPin;
  pinMode(ledPin, OUTPUT);
  pinMode(configButtonPin, INPUT_PULLUP);
}

bool Board::isConfigButtonPressed() {
   return ! digitalRead(configButtonPin);
}

void Board::blinkLed(int timeMs) {
  dbg("LED ON");
  setLed(HIGH);
  delay(timeMs);
  setLed(LOW);
  dbg("LED OFF");
  delay(timeMs);
}

void Board::setLed(int value) {
  digitalWrite(ledPin, value > 0 ? HIGH : LOW);
}

void Board::initialize() {

  runInitialConfigFlow();

  boardId = EEPROM.read(EEPROM_BOARD_ID_OFFSET);
  boardAddressStr = String("board_") + String(boardId, DEC);
  dbgf("Board id: %d", boardId);




}

/**
  Initial configuration flow. Board gives user a chance to reconfigure board address using configuration button.
  Press and hold this button during board boot process until signalization led will not shine for 3 seconds.
  Then wait until it will start to pulse. Each pulse increments board id by 1.
  After you set the board id, release button and wait a while. Board will pulse new id again in shorter time and then
  board id is stored in eeprom and board continues to boot normally.
**/
void Board::runInitialConfigFlow() {

  dbg("Running initial config flow")

  // check if 'config' button is pressed for 5 seconds
  for(int i = 0; i < 50; i++) {
    if(!isConfigButtonPressed()) {
      dbg("Config button not hold, continue with normal start")
      return;
    }
    delay(10);
  }

    // blink led and count hits of config button until it is not released
    setLed(1);
    delay(3000);
    setLed(0);
    delay(1000);

    // tick and count ticks when button is still hold, break when button is released
    boardId = 0;
    for(int i = 0; i < 255; i++) {
      if(!isConfigButtonPressed()) {
        dbgf("Break %d", i);
        break;
      }
      blinkLed(30);
      boardId++;
      delay(1000);
    }

    // now flash led boardId-times to give user feedback and then store boardid into eeprom
    dbgf("Board id is %d" , boardId);
    delay(2000);
    blinkBoardId();
    delay(2000);
    dbgf("Storing board id %d to eeprom", boardId);
    EEPROM.write(EEPROM_BOARD_ID_OFFSET, boardId);
}

void Board::blinkBoardId() {
  for(int i = 0; i < boardId; i++) {
    blinkLed(30);
    delay(200);
  }
}

void Board::awaitBoardConfiguration() {

  /**
    Board initialization hanshake looks like this:
    1. board assign ip address statically - by board id (which is configurable by config button). This address is always 192.168.99.X where X is 100+boardId
    2. board then sends "hello boardX" udp broadcast
    2. loxone then must respond with "boardX hi ipAddress", where ipAddress is address where board will then bind to
  **/

  dbg("Requesting board configuration");

  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,100+boardId};
  Network net;
  //net.begin(mac, IPAddress(192,168,99,100+boardId));
  net.begin(mac, IPAddress(255,255,255,255));

  while(true) {
    net.sendUdp(IPAddress(255,255,255,255), 5000, "hello " + boardAddressStr);

    // TODO receive, then return, else sleep
    for (int i = 0; i < 100; i++) {
      String response = net.receiveUdp(5000);
      if(response.length() > 0) {
        // TODO if response starts with "hi", parse line-by line then look for board_X for current board. Then parse ip address.
        dbg("Response is:");
        dbg(response);
      }
      delay(50);
    }

    delay(500);
  }

  /*
  EthernetUDP udpRecv;
  EthernetUDP udpSend;

  String boardAddressStr = String("board") + String(cfg.boardId, DEC);

  udpSend.beginPacket(IPAddress(255,255,255,255),5000);
  udpSend.write("hello ");
  udpSend.write(boardAddressStr);
  udpSend.flush();

  success = udpRecv.begin(5000);

  char buf[64];

while (true) {
  int packetSize = udpRecv.parsePacket();
     if (packetSize) {
         memset(buf, 0, sizeof(buf));
         udpRecv.read(buf, sizeof(buf));
         String cmd = String(buf);
         if (cmd.startsWith(boardAddressStr)) {
             cmd.replace(boardAddressStr, "");
             cmd.trim();
             dbgf("Received initial configuration: %s", cmd);
             // TODO parse board ip address
             // TODO get loxone ip address from config packet
             return;
         }
       }

    //delay(1000);
  }
  */
}
