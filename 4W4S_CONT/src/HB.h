#include "Arduino.h"

#ifndef H_BRIDGE
#define H_BRIDGE

class HB
{
  public:
  enum direct{FORWARD,REVERSE};
  HB(byte pwmP,byte dirP);
  void drive(byte dutyCyle, bool dir); //sets the pwm dutyratio
  void drive(byte dutyCyle,enum direct); //enum overload
  void drive(int dutyCyle);
  private:
  byte pwmPin; //pwm control pin
  byte dirPin; //directional pin
};
#endif
