#!/usr/bin/env bash

# syntax:
# upload file.hex /dev/ttyUSBx

FILE=$1
PORT=$2

echo $FILE | grep nano && ~/opt/arduino/hardware/tools/avr/bin/avrdude -C ~/opt/arduino/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -carduino -P${PORT} -b115200  -Uflash:w:$FILE:i
echo $FILE | grep mega && echo TODO mega