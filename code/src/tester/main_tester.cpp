
#include "Arduino.h"
#include "Wire.h"
#include "../common/mcp.h"
#include "../common/dbg.h"

Adafruit_MCP23017 mcp_out;
Adafruit_MCP23017 mcp_in;
int outputId = -1;
int inputId = -1;


void setOutputs(String outputs) {
    mcp_out.begin(outputId);
    //dbg("Set outputs to %s", outputs.c_str());
    for (int i = 0; i < 16; i++) {
        mcp_out.pinMode(i, OUTPUT);
        //dbgn(outputs[i]);
        mcp_out.digitalWrite(i, outputs[i] == '1' ? HIGH : LOW);
    }
}

String readInputs() {
    String ret = "0000000000000000";
    mcp_in.begin(inputId);
    uint16_t ab = mcp_in.readGPIOAB();
    for(int i = 0; i < 16; i++) {
        if(ab & 1) {
            ret[i] = '1';
        }
        ab>>=1;
    }
    return ret;
}

void checkPattern(char* pattern, int sleepTime) {
    dbg("Checking %s", pattern);
    String out(pattern);
    setOutputs(out);
    delay(10);
    String ret1 = readInputs();
    delay(sleepTime);
    String ret2 = readInputs();
    if(! (ret1.equals(out) && ret2.equals(out))) {
        dbg("ERROR !!!! Pattern\n%s failed as\n%s\n\n !!!!!!!!!!!!!!!!!!!!!!!!!!!\n", pattern, ret2.c_str());
        delay(1000000);
    }
}



void setup() {

    Serial.begin(9600);
    Serial.println("Make sure inputboard has higher address than output board");

    Wire.begin();
    for (int i = 0; i < 8; i++) {
        Wire.beginTransmission(i + MCP23017_ADDRESS);
        int error = Wire.endTransmission();
        if (error == 0) {
            dbg("Found board at address: %d", i);
            if (outputId == -1) {
                outputId = i;
            } else {
                inputId = i;
            }
        }
    }

    if(outputId == -1 || inputId == -1) {
        dbgn("Boards not found, fix and reset")
        delay(100000);
    }

    dbg("Output board address: %d", outputId);
    dbg("Input board address: %d", inputId);

    mcp_in.begin(inputId);
    for(int i = 0; i < 16; i++) {
        mcp_in.pinMode(i, INPUT);
        mcp_in.pullUp(i, 1);
    }

}

void loop() {

    checkPattern("1111000011001101", 100);
    checkPattern("0000000000000000", 100);
    checkPattern("1111111111111111", 100);
    checkPattern("1110001110001110", 100);
    checkPattern("1111111111111111", 1000);
    checkPattern("0000000000000000", 1000);
    checkPattern("0111001010100100", 1000);
    checkPattern("0000000000000000", 20);
    checkPattern("1101010101010101", 1000);
    checkPattern("0000000000000000", 20);
    checkPattern("0010101011111010", 1000);
    checkPattern("0000000000000000", 20);
    checkPattern("1010101111110110", 1000);
    checkPattern("0000000000000000", 20);
    checkPattern("1110101010101010", 1000);
    checkPattern("0000000000000000", 20);
    char pattern[17];

    for(int i = 0; i < 16; i++ ) {
        memset(pattern, '0', 16);
        pattern[16]=0;
        pattern[i] = '1';
        checkPattern(pattern, 300);
    }

    for(int i = 15; i >= 0; i-- ) {
        memset(pattern, '0', 16);
        pattern[i] = '1';
        checkPattern(pattern, 300);
    }

    dbgn("\n\n---------------------------------------------------\n    BOARDS ARE OK\n---------------------------------------------------\n\n");
    delay(10000);


}