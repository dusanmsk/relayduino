/**
 With UDP syntax of commands changed a bit, because it must contain master board id.

 Example command:
 om0 b2 r3 1;

 Means:
 Set master board 0 -> slave board 2 -> relay 3 -> on

 */

#include "../release.h"
#include "../common/Globals.h"
#include "../common/MasterBoard.h"
#include "../common/dbg.h"
#include <Ethernet.h>
#include <SPI.h>
#include <Wire.h>
#include "../common/mcp.h"
#include "RelayBoard.h"
#include "../common/Timer.h"
#include "../common/networking.h"

MasterBoard masterBoard;
Timer pingTimer;

#define NUM_OF_RELAY_BOARDS 8
RelayBoard* relayBoards[NUM_OF_RELAY_BOARDS] = { new RelayBoard(0), new RelayBoard(1), new RelayBoard(2), new RelayBoard(3), new RelayBoard(4), new RelayBoard(5), new RelayBoard(6), new RelayBoard(7) };

int masterBoardId;
char masterBoardIdStr[5];
int masterBoardIdStrLen;

char recvBuffer[recvBufferSize];
char sendBuffer[sendBufferSize];

int failedPings = 0;

void (*uglyResetTheBoard)(void) = 0; //declare reset function @ address 0 - ugly hard hack that works

void setup() {
    Serial.begin(9600);

    masterBoardId = masterBoard.getId();
    snprintf(masterBoardIdStr, 5, "om%d", masterBoardId);
    masterBoardIdStrLen = strlen(masterBoardIdStr);
    dbg("Master board id: %s", masterBoardIdStr);

    // relayboards starts at 192.168.100.140
    initNetwork(140 + masterBoardId);

    int error;
    Wire.begin();
	for (int adr = 0; adr < NUM_OF_RELAY_BOARDS; adr++) {
		Wire.beginTransmission(adr + MCP23017_ADDRESS);
		error = Wire.endTransmission();
		if (error == 0) {
			dbg("Found output board at address: %d", adr);
		}
	}

    // initialize relay boards
    for (int i = 0; i < NUM_OF_RELAY_BOARDS; i++) {
        RelayBoard* relayBoard = relayBoards[i];
        relayBoard->initialize();
    }
    pingTimer.sleep(PING_TIMEOUT_MS);

    masterBoard.initBlink();

    // send hello
	snprintf(sendBuffer, sendBufferSize, "hello om%d", masterBoardId);
	send(sendBuffer);

}

bool alreadyConnected;
int relayBoardId, relayId, relayValue, parsedArgs, parsedMasterBoardId;
boolean isOnline;

void loop() {
    if (receiveMessage(recvBuffer, recvBufferSize)) {
        //dbg("Received %s", recvBuffer)

       	// process ping command
		if (strncmp(recvBuffer, "ping", recvBufferSize) == 0) {
			isOnline = true;
			pingTimer.sleep(PING_TIMEOUT_MS);
			masterBoard.blinkInfoLed(30);
			masterBoard.setErrorLed(false);
			snprintf(sendBuffer, sendBufferSize, "%s pong", masterBoardIdStr);
			send(sendBuffer);
		}

        // if it was not ping command, check if command is for this masterboard
        else if (strncmp(recvBuffer, masterBoardIdStr, masterBoardIdStrLen) == 0) {
            parsedArgs = sscanf(recvBuffer, "om%d b%d r%d %d", &parsedMasterBoardId, &relayBoardId, &relayId, &relayValue);
            if (parsedArgs == 4 && parsedMasterBoardId == masterBoardId) {
                pingTimer.sleep(PING_TIMEOUT_MS);
                masterBoard.blinkInfoLed(30);
                masterBoard.setErrorLed(false);
                relayId--;
                RelayBoard* relayBoard = relayBoards[relayBoardId];
                relayBoard->setRelay(relayId, relayValue);
                relayBoard->sendData();
                dbg("Relay %d/%d set to %d", relayBoardId, relayId, relayValue)
            }
        }
    }

    // process ping timeout - possible connection lost - turn everything off immediately
    if (pingTimer.isOver()) {
        dbgn("No ping - connection lost? Turning everything off");
        isOnline = false;
        for (int i = 0; i < NUM_OF_RELAY_BOARDS; i++) {
            RelayBoard* relayBoard = relayBoards[i];
            for (int r = 0; r < 16; r++) {
                relayBoard->setRelay(r, 0);
            }
            relayBoard->sendData();
        }
        pingTimer.sleep(PING_TIMEOUT_MS);
        masterBoard.setErrorLed(true);
        if (failedPings++ > 10) {
            dbgn("No ping for a long time, trying to reset the device");
            delay(5000);
            uglyResetTheBoard();
        }

    }

    masterBoard.loop();

}
