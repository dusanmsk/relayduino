# Content

# Preparation

Arduino Nano is the actual platform. To sucessfully use arduino nano on masterboard you need
to flash optiboot bootloader to it. There is script which uploads optiboot to arduino nano using usbtiny in code/bootloader.
It requires usbtinyisp board connected to arduino nano and arduino ide to be installed. Flash take around 3 seconds.

When done, connect arduino nano using usb cable to pc and use XLoader utility to flash required firmware.
Use input or outputmaster_firmware_nano328.hex files, setup xloader as following:
- hex file: specify firmware file
- device: Uno (atmega 328)
- com port: where your nano is
- baud rade: 115200

Leds will flash during update.

To check nano was flashed succesfully, close xloader, then start arduino ide, choose board "Adruino/Genuino UNO", specify port
and start serial monitor. If you will see messages such as:

Master board id: im0
Assigned address: 192.168.88.120
No ping - connection lost?
...

you have flashed sucessfully.
   
 


TODO

# How to connect

Connect input slave boards to input master board using XH cable. Same situation for output board


# Flashing firmware

On Windows use XLoader (http://xloader.russemotto.com/), on linux use avrdude. Download and flash right firmware depending on board you are flashing.


# Loxone

At first you need to create new virtual output, name "Relayduino output BUS", address /dev/udp/255.255.255.255/6666, separator ";". Then create new output command named "ping", command for ON: "ping"
and feed it with pulse generator configured 1 on 4 off seconds. Boards use this ping to detect network failures and this command is mandatory. When output board lost this command
for a while, it turns off all relays.

To drive single relay on masterboard=0, slaveboard=2, relay=3, create new output command with following configuration:
```
Command ON: om0 b2 r3 1
Command OFF: om0 b2 r3 0
First repetition: 30
Repetition interval: 30
Use as digital output
```

To receive signals from inputboards, create new udp virtual input named "Relayduino input BUS", udp receive port 5555. You should use udp monitor then to create commands from input packets.
If you would like to do so manually, structure of command is:
"im0 b3 i6 1" - means "Input 6 on slave board 3 of input masterboard 0 is ON".

Tip: if you would like to handle "long press" of button, you need to configure it as "im0 b3 i6 \v" and uncheck "use as digital input".
