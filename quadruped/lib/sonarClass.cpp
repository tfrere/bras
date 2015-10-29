#include "sonarClass.hpp"

void SonarClass::init(int pin1, int pin2)
{
    trig = pin1;
    echo = pin2;
    pinMode(trig, OUTPUT); 
    digitalWrite(trig, LOW); 
    pinMode(echo, INPUT); 
}

int SonarClass::getDist()
{
    digitalWrite(trig, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig, LOW); 
    lecture_echo = pulseIn(echo, HIGH); 
    cm = lecture_echo / 58; 
    Serial.print("Distance cm : "); 
    Serial.println(cm); 
    return (cm);
}
