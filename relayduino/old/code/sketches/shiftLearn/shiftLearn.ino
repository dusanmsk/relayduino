

class ShiftOut {

  private:
    int pinData ;
    int pinOutputEnable ;
    int pinReset ;
    int pinShiftClock ;
    int pinLatchClock ;


    void resetShiftRegister() {
      digitalWrite(pinReset, LOW);
      digitalWrite(pinReset, HIGH);
    }

  public:

    ShiftOut(int pinData, int pinOutputEnable, int pinReset, int pinShiftClock, int pinLatchClock) {
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
      
      this->pinData = pinData;
      this->pinOutputEnable = pinOutputEnable;
      this->pinReset = pinReset;
      this->pinShiftClock = pinShiftClock;
      this->pinLatchClock = pinLatchClock;
    }
    
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

ShiftOut out(53,51,45,47,49);
void setup() {
  Serial.begin(9600);
}

void loop1() {
  int d1[] = {1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1};
  out.send(d1,16);
  delay(5000000);
}

void loop() {
  int d1[] = {1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0};
  int d0[] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1};
  out.send(d1,16);
  delay(500);
  out.send(d0,16);
  delay(500);
}
