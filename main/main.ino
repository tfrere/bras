#include <Servo.h>

Servo servomoteur1, servomoteur2, servomoteur3;
int posMoteur1 = 90, posMoteur2 = 90, posMoteur3 = 90, posMoteur4 = 90, posMoteur5 = 90;

void setup()
{

  Serial.begin(9600);
  servomoteur1.attach(2);
  servomoteur2.attach(3);
  servomoteur3.attach(4);
  servomoteur4.attach(5);
  servomoteur5.attach(6);
  servomoteur1.write(posMoteur1);
  servomoteur2.write(posMoteur2);
  servomoteur3.write(posMoteur3);
  servomoteur4.write(posMoteur4);
  servomoteur5.write(posMoteur5);

}

void updatePos()
{
  servomoteur1.write(posMoteur1);
  servomoteur2.write(posMoteur2);
  servomoteur3.write(posMoteur3);
  servomoteur4.write(posMoteur4);
  servomoteur5.write(posMoteur5);
}
void loop()
{
  posMoteur1 = posMoteur2 = posMoteur3 = posMoteur4 = posMoteur5 = 5;
  updatePos();
  sleep(1);
  posMoteur1 = posMoteur2 = posMoteur3 = posMoteur4 = posMoteur5 = 150;
  updatePos();
  sleep(1);
}
