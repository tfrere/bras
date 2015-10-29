#include <Servo.h> 
#include "lib/servoClass.hpp"
#include "lib/servoClass.cpp"
#include "lib/sonarClass.hpp"
#include "lib/sonarClass.cpp"


ServoClass frontLeftArm[3];

void setup()
{
  Serial.begin(9600); 

  delay(250);

  frontLeftArm[0].init(12);
  frontLeftArm[1].init(10);
  frontLeftArm[2].init(8);

  frontLeftArm[0].easeTo(0);
  frontLeftArm[1].easeTo(0);
  frontLeftArm[2].easeTo(0);
  frontLeftArm[0].setSpeed(0.15);
  frontLeftArm[1].setSpeed(0.15);
  frontLeftArm[2].setSpeed(0.15);

}

void walkCycle() {
  // moitié
  frontLeftArm[1].easeTo(40);
  frontLeftArm[2].easeTo(30);
  delay(150);
  frontLeftArm[0].easeTo(40); // tourne un peu  
  frontLeftArm[1].easeTo(130); // descends l'articulation
  frontLeftArm[2].easeTo(90); // pose la patte  
}

void loop() 
{ 

  walkCycle();
  frontLeftArm[0].easeTo(0);
  delay(300);
  
}


