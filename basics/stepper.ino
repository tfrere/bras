#include <math.h>

#define STP_SPEED 1200
#define STP1 53
#define STP2 51
#define STP3 49
#define STP4 47

int lookUp[8] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001 };


void  setOutput(int out) {
  digitalWrite(STP1, bitRead(lookUp[out], 0));
  digitalWrite(STP2, bitRead(lookUp[out], 1));
  digitalWrite(STP3, bitRead(lookUp[out], 2));
  digitalWrite(STP4, bitRead(lookUp[out], 3));
}

void  clockwise() {
  if (count < 90) {
    for (int i=0; i < 8; ++i) {
      setOutput(i);
      delayMicroseconds(STP_SPEED);
    }
    count++;
  }
}

void  counterclockwise() {
  if (count > -300) {
    for (int i=7; i >= 0; --i) {
      setOutput(i);
      delayMicroseconds(STP_SPEED);
    }
    count--;
  }
}

void setup()
{
  Serial.begin(9600);

  pinMode(STP1, OUTPUT);
  pinMode(STP2, OUTPUT);
  pinMode(STP3, OUTPUT);
  pinMode(STP4, OUTPUT);

}

void loop()
{
	clockwise();
	delayMicroseconds(2500);
}
