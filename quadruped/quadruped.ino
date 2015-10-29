// #include <Servo.h> 
// #include "lib/servoClass.hpp"
// #include "lib/servoClass.cpp"
// #include "lib/sonarClass.hpp"
// #include "lib/sonarClass.cpp"


// ServoClass frontLeftArm[3];
// ServoClass frontRightArm[3];
// ServoClass backLeftArm[3];
// ServoClass backRightArm[3];

// SonarClass sonar;

// void setup()
// {
//   Serial.begin(9600); 
//   sonar.init(33, 35);

//   delay(250);

//   frontLeftArm[0].init(24);
//   frontLeftArm[1].init(26);
//   frontLeftArm[2].init(28);

//   frontLeftArm[0].easeTo(0);
//   frontLeftArm[1].easeTo(0);
//   frontLeftArm[2].easeTo(0);

// delay(250);

//   backLeftArm[0].init(48); // old 40 42 44
//   backLeftArm[1].init(50);
//   backLeftArm[2].init(52);
  
//   backLeftArm[0].easeTo(0);
//   backLeftArm[1].easeTo(0);
//   backLeftArm[2].easeTo(0);

// delay(250);

//   // old 40 130 90

//   frontRightArm[0].init(32);
//   frontRightArm[1].init(34);
//   frontRightArm[2].init(36);

//   frontRightArm[0].easeTo(40); 
//   frontRightArm[1].easeTo(130);
//   frontRightArm[2].easeTo(90);

// delay(250);

//   backRightArm[0].init(40);
//   backRightArm[1].init(42);
//   backRightArm[2].init(44);
  
//   backRightArm[0].easeTo(40);
//   backRightArm[1].easeTo(130);
//   backRightArm[2].easeTo(90);

// }

// void walkCycle() {
//   // moitié
//   frontLeftArm[1].easeTo(40);
//   frontLeftArm[2].easeTo(30);
//   delay(150);
//   frontLeftArm[0].easeTo(40); // tourne un peu  
//   frontLeftArm[1].easeTo(130); // descends l'articulation
//   frontLeftArm[2].easeTo(90); // pose la patte
  
//   delay(300);

//   backRightArm[1].easeTo(40);
//   backRightArm[2].easeTo(30);
//   delay(150);
//   backRightArm[0].easeTo(0); // tourne un peu
//   backRightArm[1].easeTo(0);
//   backRightArm[2].easeTo(0);

//   delay(300);

//   backLeftArm[1].easeTo(40);
//   backLeftArm[2].easeTo(30);
//   delay(150);
//   backLeftArm[0].easeTo(40); // tourne un peu  
//   backLeftArm[1].easeTo(130);
//   backLeftArm[2].easeTo(90);

//   delay(300);

//   frontRightArm[1].easeTo(40);
//   frontRightArm[2].easeTo(30);
//   delay(150);
//   frontRightArm[0].easeTo(0); // tourne un peu
//   frontRightArm[1].easeTo(0);
//   frontRightArm[2].easeTo(0);

//   delay(300);

// }

// void loop() 
// {
//   if (sonar.getDist() >= 30)
//     walkCycle();
 
//   frontLeftArm[0].easeTo(0);
//   backLeftArm[0].easeTo(0);
//   frontRightArm[0].easeTo(40);
//   backRightArm[0].easeTo(40);
//   delay(300);
  
// }


