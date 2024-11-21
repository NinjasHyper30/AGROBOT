#include "Arduino.h"
#include "HB.h"

HB::HB(byte pwmP,byte dirP)
:pwmPin(pwmP),dirPin(dirP)
{
  pinMode(pwmPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
}

void HB::drive(byte dutyCyle,bool dir)
{
  analogWrite(pwmPin,dutyCyle);
  digitalWrite(dirPin,dir);
}
void HB::drive(byte dutyCyle,enum direct dir)
{
  analogWrite(pwmPin,dutyCyle);
  digitalWrite(dirPin,dir);
}
void HB::drive(int dutyCycle)
{
  bool dir=(dutyCycle<0);
  drive(dutyCycle,dir);
}
