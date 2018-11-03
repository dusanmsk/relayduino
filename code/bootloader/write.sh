#!/bin/bash
~/opt/arduino/hardware/tools/avr/bin/avrdude -C ~/opt/arduino/hardware/tools/avr/etc/avrdude.conf -v -patmega328p -cusbtiny -Uflash:w:optiboot_atmega328.hex:i -Ulock:w:0x0F:m 
