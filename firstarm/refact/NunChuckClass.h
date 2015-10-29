
class WiiChuck {

  private:
    uint8_t cnt;
    uint8_t status[6];      // array to store wiichuck output
    uint8_t averageCounter;
    int i;
    int total;
    uint8_t zeroJoyX;   // these are about where mine are
    uint8_t zeroJoyY; // use calibrateJoy when the stick is at zero to correct
    int lastJoyX;
    int lastJoyY;
    int angles[3];

    bool lastZ, lastC;

  public:
    uint8_t joyX;
    uint8_t joyY;
    bool buttonZ;
    bool buttonC;
    void begin()
    {
      Wire.begin();
      cnt = 0;
      averageCounter = 0;
      // instead of the common 0x40 -> 0x00 initialization, we
      // use 0xF0 -> 0x55 followed by 0xFB -> 0x00.
      // this lets us use 3rd party nunchucks (like cheap $4 ebay ones)
      // while still letting us use official oness.
      // only side effect is that we no longer need to decode bytes in _nunchuk_decode_byte
      Wire.beginTransmission(0x52);   // device address
      Wire.write(0xF0);
      Wire.write(0x55);
      Wire.endTransmission();
      delay(1);
      Wire.beginTransmission(0x52);
      Wire.write(0xFB);

      Wire.write(0x01);
      Wire.write((uint8_t)0x00);

      Wire.endTransmission();
      update();           
      for (i = 0; i<3;i++) {
        angles[i] = 0;
      }
      zeroJoyX = DEFAULT_ZERO_JOY_X;
      zeroJoyY = DEFAULT_ZERO_JOY_Y;
    }

    void calibrateJoy() {
      zeroJoyX = joyX;
      zeroJoyY = joyY;
    }

    void update() {

      Wire.requestFrom (0x52, 6); // request data from nunchuck
      while (Wire.available ()) {
        // receive byte as an integer
        status[cnt] = _nunchuk_decode_byte (Wire.read()); //
        cnt++;
      }
      if (cnt > 5) {
        lastZ = buttonZ;
        lastC = buttonC;
        lastJoyX = readJoyX();
        lastJoyY = readJoyY();
        //averageCounter ++;
        //if (averageCounter >= AVERAGE_N)
        //    averageCounter = 0;

        cnt = 0;
        joyX = (status[0]);
        joyY = (status[1]);
        for (i = 0; i < 3; i++)
          //accelArray[i][averageCounter] = ((int)status[i+2] << 2) + ((status[5] & (B00000011 << ((i+1)*2) ) >> ((i+1)*2)));
          angles[i] = (status[i+2] << 2) + ((status[5] & (B00000011 << ((i+1)*2) ) >> ((i+1)*2)));

        //accelYArray[averageCounter] = ((int)status[3] << 2) + ((status[5] & B00110000) >> 4);
        //accelZArray[averageCounter] = ((int)status[4] << 2) + ((status[5] & B11000000) >> 6);

        buttonZ = !( status[5] & B00000001);
        buttonC = !((status[5] & B00000010) >> 1);
        _send_zero(); // send the request for next bytes

      }
    }

    float readAccelX() {
      // total = 0; // accelArray[xyz][averageCounter] * FAST_WEIGHT;
      return (float)angles[0] - ZEROX;
    }
    float readAccelY() {
      // total = 0; // accelArray[xyz][averageCounter] * FAST_WEIGHT;
      return (float)angles[1] - ZEROY;
    }
    float readAccelZ() {
      // total = 0; // accelArray[xyz][averageCounter] * FAST_WEIGHT;
      return (float)angles[2] - ZEROZ;
    }

    bool zPressed() {
      return (buttonZ); // && ! lastZ
    }
    bool cPressed() {
      return (buttonC);
    }

    int readJoyX() {
      return (int) joyX - zeroJoyX;
    }

    int readJoyY() {
      return (int)joyY - zeroJoyY;
    }

  private:
    uint8_t _nunchuk_decode_byte (uint8_t x)
    {
      //decode is only necessary with certain initializations
      //x = (x ^ 0x17) + 0x17;
      return x;
    }

    void _send_zero()
    {
      Wire.beginTransmission (0x52);  // transmit to device 0x52
      Wire.write ((uint8_t)0x00);     // sends one byte
      Wire.endTransmission ();    // stop transmitting
    }

};
/* end class nunchuck */
