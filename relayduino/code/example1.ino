
int dataPin = 2;
int outputEnablePin = 3;
int rclkPin = 4;
int srclkPin = 5;

int sleepTime = 1000;

#define dbgs(x) Serial.println(x); delay(sleepTime);

void setup() {
  Serial.begin(9600);
  pinMode(dataPin, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);
  pinMode(rclkPin, OUTPUT);
  pinMode(srclkPin, OUTPUT);

  digitalWrite(outputEnablePin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(rclkPin, LOW);
  digitalWrite(srclkPin, LOW);
}

void writeBit(int bitValue) {
    
    digitalWrite(dataPin, bitValue > 0 ? HIGH : LOW);
    digitalWrite(srclkPin, HIGH);
    delay(50);
    digitalWrite(srclkPin, LOW);
    Serial.print("Written ");
    Serial.println(bitValue, DEC);
    delay(sleepTime/4);
}

void foo(int i) {
}

void loop() {

    writeBit(1);
    writeBit(0);
    writeBit(0);
    writeBit(1);
    writeBit(0);
    writeBit(0);
    writeBit(1);
    writeBit(0);
    
    digitalWrite(rclkPin, HIGH);
    digitalWrite(rclkPin, LOW);

    digitalWrite(outputEnablePin, LOW);

    delay(600000);

} 