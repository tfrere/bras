#include <Servo.h>

Servo servomoteur;
int posMoteur = 0;

void setup()
{
  Serial.begin(9600);
  servomoteur.attach(2); // mettre le numéro de la pin que t'as choisi sur l'arduino

}

void loop()
{
  int i = 0;

  while (i <= 360)
  {
    servomoteur.write(i);
    delayMicroseconds(2500); // là ou tu changes le délais pour caller avec l'appareil photo
    i += 20;
  }

}
