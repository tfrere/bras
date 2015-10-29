#include "servoClass.hpp"

void ServoClass::reset()
{
    currPos = 0;    
}

void ServoClass::init(int pin)
{
    servo.attach(pin, 1000, 2000);
    servocon = 0.05; // default speed
    //reset();
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