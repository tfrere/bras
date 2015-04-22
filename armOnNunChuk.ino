#include <Wire.h>
#include <math.h>
#include <Servo.h>

// these may need to be adjusted for each nunchuck for calibration
#define ZEROX 510 
#define ZEROY 490
#define ZEROZ 460

#define DEFAULT_ZERO_JOY_X 124
#define DEFAULT_ZERO_JOY_Y 132

#define STP_SPEED 1200
#define STP1 53
#define STP2 51
#define STP3 49
#define STP4 47

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


WiiChuck chuck = WiiChuck();

Servo servomoteur1, servomoteur2, servomoteur3;
int posMoteur1 = 90, posMoteur2 = 90, posMoteur3 = 90;
int mode=0;
int sensibility=1;
int	count=0;
int countPerRev=512;
int lookUp[8] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001 };

void mode_joystick(int a, int b){
 
    if(a < -50){ // gauche
      if(posMoteur1 > 10){
        posMoteur1 += sensibility*a/50;
				posMoteur1 = posMoteur1 < 10 ? 10 : posMoteur1;
        servomoteur1.write(180-posMoteur1);
      }
    }

    if(a > 50){ //droite
      if(posMoteur1 < 170){
        posMoteur1 += sensibility*a/50;
				posMoteur1 = posMoteur1 > 170 ? 170 : posMoteur1;
        servomoteur1.write(180-posMoteur1);
      }
    }

    if(b > 50){ //haut
      if(posMoteur2 < 170){
        posMoteur2 += sensibility*b/50;
				posMoteur2 = posMoteur2 > 170 ? 170 : posMoteur2;
        servomoteur2.write(posMoteur2);
      }
    }

    if(b < -50){ //bas
      if(posMoteur2 > 10){
        posMoteur2 += sensibility*b/50;
				posMoteur2 = posMoteur2 < 10 ? 10 : posMoteur2;
        servomoteur2.write(posMoteur2);
      }
    }
}

void  activateClaw() {
    posMoteur3 += 1;
    if (posMoteur3 > 170)
      posMoteur3 = 170;
    servomoteur3.write(posMoteur3);
}


void	setOutput(int out) {
	digitalWrite(STP1, bitRead(lookUp[out], 0));
	digitalWrite(STP2, bitRead(lookUp[out], 1));
	digitalWrite(STP3, bitRead(lookUp[out], 2));
	digitalWrite(STP4, bitRead(lookUp[out], 3));
}

void	clockwise() {
	if (count < 90) {
		for (int i=0; i < 8; ++i) {
			setOutput(i);
			delayMicroseconds(STP_SPEED);
		}
		count++;
	}
}

void	counterclockwise() {
	if (count > -90) {
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
  servomoteur1.attach(2);
  servomoteur2.attach(3);
  servomoteur3.attach(4);


  servomoteur1.write(90);
  servomoteur2.write(90);
  servomoteur3.write(90);

	pinMode(STP1, OUTPUT);
	pinMode(STP2, OUTPUT);
	pinMode(STP3, OUTPUT);
	pinMode(STP4, OUTPUT);

  chuck.begin();
}

void loop()
{
  chuck.update(); // on actualise les donnÃ©es du nunchuk

  if(chuck.zPressed())  // on remet les moteurs à la position de départ
  {
    //posMoteur1 = 90;
    //posMoteur2 = 90;
    //posMoteur3 = 90;
    //servomoteur1.write(posMoteur1);
    //servomoteur2.write(posMoteur2);
    //servomoteur3.write(posMoteur3);
    activateClaw();
  }
  else
  {
      posMoteur3 = 90;
      servomoteur3.write(posMoteur3);
  }

	int a = chuck.readJoyX();
	int b = chuck.readJoyY();
	int zVel = chuck.readAccelZ();

	if(chuck.cPressed())
	{
		zVel = constrain(zVel, -180, 180);
		zVel = map(zVel, -180, 180, 0, 180);
		if (zVel > 90)
			clockwise();
		else
			counterclockwise();
		mode_joystick(a, b);
	}
	else {
		mode_joystick(a, b);
		delayMicroseconds(2500);
	}
	

  
  //un petit delai d'attente pour ne pas saturer des servomoteurs
}
