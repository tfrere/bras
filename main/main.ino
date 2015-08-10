#include <Servo.h>
#include <Wire.h>
#include <math.h>


Servo servomoteur[5];
int posMoteur[5];

void setup()
{

  Serial.begin(9600);
  servomoteur[0].attach(6);
  servomoteur[1].attach(5);
  servomoteur[2].attach(3);
  servomoteur[3].attach(2);
  servomoteur[4].attach(4);
  int i = 0;
  while (i < 5)
  {
    posMoteur[i] = 180;
    servomoteur[i].write(posMoteur[i]);
    i++;
  }
}

void updatePos()
{
  int i = 0;
  while (i < 5)
  {
    servomoteur[i].write(posMoteur[i]);
    i++;
  }
  delay(500);
}

void  chiFuMi()
{
  // FEUILLE
  posMoteur[0] = posMoteur[1] = posMoteur[2] = posMoteur[3] = posMoteur[4] = 0;
  updatePos();
  delay(2500);
  // PIERRE
  posMoteur[0] = posMoteur[1] = posMoteur[2] = posMoteur[3] = posMoteur[4] = 180;
  updatePos();
  delay(2500);
  // YO
  posMoteur[0] = posMoteur[1] = 180;
  posMoteur[2] = posMoteur[3] = posMoteur[4] = 0;
  updatePos();
}


void  count()
{
  int i = 4;
  while (i >= 0)
  {
    int j = i;
    while (j <=4)
    {
      posMoteur[j] = 0;
      j++;
    }
    updatePos();
    int k = 0;
    while (k < 5)
    {
      posMoteur[k] = 180;
      k++;
    }
    updatePos();
    i--;
  }
}

void  wave()
{
  while (42)
  {
    int    i = 0;
    while (i < 5)
    {
      posMoteur[i] = 180;
      i++;
    }
    updatePos();
    i = 0;
    while (i < 5)
    {
      posMoteur[i] = 0;
      updatePos();
      i++;
    }
    i = 4;
    while (i >= 0)
    {
      posMoteur[i] = 180;
      updatePos();
      i--;
    }
  }
}

void loop()
{

  //wave();
  count();
  //FUCK
  posMoteur[2] = 0;
  posMoteur[1] = posMoteur[3] = posMoteur[0] = 180;
  updatePos();
  delay(2500);
  posMoteur[1] = posMoteur[3] = posMoteur[0]= posMoteur[2] = 180;
  updatePos();



}

