"c:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude.exe" -C"c:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf"  -v -patmega328p -cusbtiny -Uflash:w:optiboot_atmega328.hex:i -Ulock:w:0x0F:m