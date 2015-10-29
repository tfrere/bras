#ifndef SERVOCLASS_H
    #define SERVOCLASS_H

    #include <Arduino.h>
    #include <string.h> 

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
             void init(int pin);
             void reset();
             void easeTo(int cposition);
             void goTo(int cposition);
             void setSpeed(float speed);
    };


#endif
