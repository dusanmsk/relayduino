### Addressing
Dip switch has "mirrored logic", so to set right address you need to convert address to binary
and then switch 1 with 0.

So:
- 0 = on on on
- 1 = on on off
- 2 = on off on
- 3 = on off off
- 4 = off on on
- 5 = off on off
- 6 = off off on
- 7 = off off off

### BOM
ULN1, ULN2 = ULN2803A (+ optional socket DIP18)
DIP1 = 3 position dip switch
LED1 = green led
OPTO1,2,3,4 = K847ph + socket
R1 = 220
R2,3,6,7 = 4608X-102-103LF
R4,5,8,9 = 4608X-102-102LF
R10 = 4605x-101-102LF
J1 = 4 pin 2.54mm jst xh female
C1 = 100n keramic
C2 = 100p keramic
MCP1 =  MCP23017-E/SP (+ optional socket)
2x "ebay PCB Din C45 Rail Adapter 35mm"
2x 8pin 5.08 socket
1x 2pin 5.08 socket
