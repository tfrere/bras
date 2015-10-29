#ifndef SONARCLASS_H
    #define SONARCLASS_H

    #include <Arduino.h>
    #include <string.h> 

    class SonarClass 
    {
        private:
            int trig = 33; 
            int echo = 35; 
            long lecture_echo; 
            long cm;

        public:
             void init(int pin1, int pin2);
             int  getDist();
    };


#endif
