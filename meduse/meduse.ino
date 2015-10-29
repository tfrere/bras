
#include <Servo.h>   

class ServoClass 
{
private:
    Servo servo;      // what servo we're operating on
    int currPos;
    float timeAngle;
    float timeAngleadjust;
    float moveAngle;             
    int oldposition;
    float servocon;
    float sfactor;

public:
     void init(Servo s, int pin);
     void reset();
     void easeTo(int cposition);
     void goTo(int cposition);
     void setSpeed(float speed);

};

void ServoClass::reset()
{
    currPos = 0;    
}


void ServoClass::init(Servo s, int pin)
{
    servo = s;
    servo.attach(pin);
    servocon = 0.05; // default speed
    reset();
}

void ServoClass::setSpeed(float speed)
{
    servocon = speed;
}

void ServoClass::goTo(int cposition)
{
    servo.write(cposition);
}

void ServoClass::easeTo(int cposition) {
  
     int anglediff = abs(cposition-oldposition);
     sfactor = servocon/anglediff; 
     for (timeAngle=0.000; timeAngle<=1;) { 
       timeAngle = timeAngle+sfactor;
       timeAngleadjust = (1.0/2.0) - (1.0/2.0*cos(timeAngle*PI));
       moveAngle = (anglediff*timeAngleadjust);
       int calangle;
       if (oldposition > cposition) {
         calangle =  oldposition - (int)moveAngle;
       }
       if (oldposition < cposition) {
         calangle =  oldposition + (int)moveAngle ;
       }
       
       servo.write(calangle); 
     }
     oldposition = cposition;
     
} 

Servo test;
ServoClass myServo;

void setup() {
   Serial.begin(19200);
   
   myServo.init(test, 7);
   myServo.reset();
}

void loop() {
  myServo.goTo(100);
  delay(1000);
  myServo.goTo(0);
  delay(1000);
}

