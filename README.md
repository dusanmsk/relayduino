# Content

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
