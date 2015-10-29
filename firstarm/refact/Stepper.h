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
