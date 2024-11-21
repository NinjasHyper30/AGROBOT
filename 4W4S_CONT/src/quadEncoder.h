
#ifndef Encoder_
#define Encoder_
#include "Arduino.h"
#define MAX_ENCODER 4
#define CONST_TOUT 1000000
class qEncoder
{
  public:
  qEncoder(byte pA,byte pB,double k);
  qEncoder(byte pA,byte pB,double k,long to);
  ~qEncoder();
  static void interrupt_0();
  static void interrupt_1();
  static void interrupt_2();
  static void interrupt_3();
  double getSpeed();
  private:
  byte pinA;  //encoder channel A
  byte pinB;  //encoder channel B
  double wc;  //speed const
  long timeOut; //timeout for min speed
  volatile long tp;    
  volatile long tc;
  volatile int dir;
  int instCnt; //instance count
  static qEncoder* _instances[MAX_ENCODER]; //pointer of instances 
};
#endif
