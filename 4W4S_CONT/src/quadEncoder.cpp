#include "quadEncoder.h"

qEncoder* qEncoder::_instances[MAX_ENCODER]={nullptr,nullptr,nullptr,nullptr};

void qEncoder::interrupt_0()
{
  _instances[0]->tp=_instances[0]->tc;
  _instances[0]->tc=micros();
  _instances[0]->dir=digitalRead(_instances[0]->pinB)?1:-1;
}
void qEncoder::interrupt_1()
{
  _instances[1]->tp=_instances[1]->tc;
  _instances[1]->tc=micros();
  _instances[1]->dir=digitalRead(_instances[1]->pinB)?1:-1;
}
void qEncoder::interrupt_2()
{
  _instances[2]->tp=_instances[2]->tc;
  _instances[2]->tc=micros();
  _instances[2]->dir=digitalRead(_instances[2]->pinB)?1:-1;
}
void qEncoder::interrupt_3()
{
  _instances[3]->tp=_instances[3]->tc;
  _instances[3]->tc=micros();
  _instances[3]->dir=digitalRead(_instances[3]->pinB)?1:-1;
}
qEncoder::qEncoder(byte pA,byte pB,double k,long to)
:pinA(pA),pinB(pB),wc(k),timeOut(to),tp(0),tc(0),dir(0)
{
  for(int i=0;i<4;i++)
  {
    if(!_instances[i])
    {
      instCnt=i;
      _instances[i]=this; break;
    }
  }
  pinMode(pinA,INPUT);
  pinMode(pinB,INPUT);
  switch(instCnt)
  {
   case 0:
   attachInterrupt(digitalPinToInterrupt(pinA),interrupt_0, RISING); 
   break;
   case 1:
   attachInterrupt(digitalPinToInterrupt(pinA),interrupt_1, RISING); 
   break;
   case 2:
   attachInterrupt(digitalPinToInterrupt(pinA),interrupt_2, RISING); 
   break;
   case 3:
   attachInterrupt(digitalPinToInterrupt(pinA),interrupt_3, RISING);
   break; 
  }
}
qEncoder::qEncoder(byte pA,byte pB,double k)
:qEncoder(pA,pB,k,CONST_TOUT)
{
  
}
double qEncoder::getSpeed()
{
  long cur=micros();
  if(cur-tc>timeOut||tc==tp)return 0;
  double dt=tc-tp;
  double ans=dir*(wc/dt);
  return ans;
}
qEncoder::~qEncoder()
{
  detachInterrupt(digitalPinToInterrupt(pinA));
  _instances[instCnt]=nullptr;
}
