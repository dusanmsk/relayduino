
    int pinData = 53;
    int pinOutputEnable = 51;
    int pinReset = 45;
    int pinShiftClock = 47;
    int pinLatchClock = 49;


class ShiftOut {

  private:

    void resetShiftRegister() {
      digitalWrite(pinReset, LOW);
      digitalWrite(pinReset, HIGH);
    }

  public:
  
    void send(int data[], int arrLen) {
      // set everything to low
      digitalWrite(pinShiftClock, LOW);
      digitalWrite(pinLatchClock, LOW);
      digitalWrite(pinData, LOW);

      resetShiftRegister();

      for (int i = arrLen - 1; i>=0; i--)  {
        // write data
        digitalWrite(pinData, data[i] > 0 ? HIGH : LOW);
    
        // tick with shift register clock
        digitalWrite(pinShiftClock, LOW);
        digitalWrite(pinShiftClock, HIGH);
        digitalWrite(pinShiftClock, LOW);
    
        // reset data pin to zero
        digitalWrite(pinData, LOW);
      }

      // now data is in the shift register(s). To "show" them, tick with latch clock and all data will be "copied" from shift register(s) to latch register(s)
      digitalWrite(pinLatchClock, LOW);
      digitalWrite(pinLatchClock, HIGH);
      digitalWrite(pinLatchClock, LOW);
    
      // enable output (this normally does nothing because output is permanently enabled)
      digitalWrite(pinOutputEnable, LOW);
    };

};




int spd = 10;

void dbg(String msg) {
  Serial.println(msg);
}

/*
void shiftOut(byte data) {
  bool pinState = false;

  // set everything to low
  digitalWrite(pinShiftClock, LOW);
  digitalWrite(pinLatchClock, LOW);
  digitalWrite(pinData, LOW);

  // reset shift register(s)
  digitalWrite(pinReset, LOW);
  digitalWrite(pinReset, HIGH);

  // send data, tick with the shift clock for each bit
  for (int i=7; i>=0; i--)  {
    pinState = ( data & (1<<i) );
    // write data
    digitalWrite(pinData, pinState);

    // tick with shift register clock
    digitalWrite(pinShiftClock, LOW);
    digitalWrite(pinShiftClock, HIGH);
    digitalWrite(pinShiftClock, LOW);

    // reset data pin to zero
    digitalWrite(pinData, LOW);
    
    //delay(10*spd);    
  }

  // now data is in the shift register. To "show" them, tick with latch clock and all data will be "copied" from shift register to latch register
  digitalWrite(pinLatchClock, LOW);
  digitalWrite(pinLatchClock, HIGH);
  digitalWrite(pinLatchClock, LOW);

  // enable output (this normally does nothing because output is permanently enabled)
  digitalWrite(pinOutputEnable, LOW);
  
  dbg("done");
}
*/

ShiftOut out;

void setup() {

  out = ShiftOut();

  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(pinData, OUTPUT);
  digitalWrite(pinData, LOW);
  
  pinMode(pinReset, OUTPUT);
  digitalWrite(pinReset, HIGH);             // HIGH = do nothing, LOW = reset shift register
  
  pinMode(pinOutputEnable, OUTPUT);
  digitalWrite(pinOutputEnable, LOW);       // LOW = enable output, pass data from latch register to outputs, HIGH = do nothing
  
  pinMode(pinShiftClock, OUTPUT);
  digitalWrite(pinShiftClock, LOW);

  pinMode(pinLatchClock, OUTPUT);
  digitalWrite(pinLatchClock, LOW);
  

}

void loop() {
  int d1[] = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};
  int d0[] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
  out.send(d1,16);
  delay(500);
  out.send(d0,16);
  delay(500);
}
