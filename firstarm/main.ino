#include <Wire.h>
#include <math.h>
#include <Servo.h>
#include "NunChukClass.h"
#include "Stepper.h"
/* NUNCHUCK
=============================== */

// need to be adjusted for each nunchuck for calibration
#define ZEROX 510 
#define ZEROY 490
#define ZEROZ 460

#define DEFAULT_ZERO_JOY_X 124
#define DEFAULT_ZERO_JOY_Y 132

/* STEPPER
=============================== */

#define STP_SPEED 1200
#define STP1 53
#define STP2 51
#define STP3 49
#define STP4 47

/* INIT
=============================== */

//WiiChuck chuck = WiiChuck();

Servo servomoteur1, servomoteur2, servomoteur3;
int posMoteur1 = 90, posMoteur2 = 90, posMoteur3 = 90;

int mode=0;
int sensibility=1;
int count=0;
int countPerRev=512;
int lookUp[8] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001 };

void mode_joystick(int a, int b){
 
    // gauche 
    if(a < -50){ 
      if(posMoteur1 > 10){
        posMoteur1 += sensibility * a / 50;
        posMoteur1 = posMoteur1 < 10 ? 10 : posMoteur1;
        servomoteur1.write(180-posMoteur1);
      }
    }
    // droite
    if(a > 50){ 
      if(posMoteur1 < 170){
        posMoteur1 += sensibility * a / 50;
        posMoteur1 = posMoteur1 > 170 ? 170 : posMoteur1;
        servomoteur1.write(180-posMoteur1);
      }
    }
    // haut
    if(b > 50){ 
      if(posMoteur2 < 140){
        posMoteur2 += sensibility * b / 50;
        posMoteur2 = posMoteur2 > 140 ? 140 : posMoteur2;
        servomoteur2.write(posMoteur2);
      }
    }
    // bas
    if(b < -50){ 
      if(posMoteur2 > 40){
        posMoteur2 += sensibility * b / 50;
        posMoteur2 = posMoteur2 < 40 ? 40 : posMoteur2;
        servomoteur2.write(posMoteur2);
      }
    }
}

void  activateClaw() {
    posMoteur3 += 1;
    if (posMoteur3 > 140)
      posMoteur3 = 140;
    servomoteur3.write(posMoteur3);
}

void setup()
{

  Serial.begin(9600);

  // init and reset servos
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

  //chuck.update(); // on actualise les donnÃ©es du nunchuk
    if (Serial.available() > 0) {
          incomingByte = Serial.read();
          Serial.print("I received: ");
          Serial.println(incomingByte, DEC);
  }
  digitalWrite(32, LOW);
  digitalWrite(34, LOW);

  if(chuck.zPressed())  // on active la pince et on allume les yeux
  {
  
    digitalWrite(32, HIGH);
    digitalWrite(34, HIGH);
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

  // delayMicroseconds(100);
  //un petit delai d'attente pour ne pas saturer des servomoteurs
}
