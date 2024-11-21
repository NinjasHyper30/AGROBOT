#include "Arduino.h"
#include "pid.h"

PID::PID(double T,double P,double I,double D,double N)
{
  kp=P; ki=I; kd=D; Nf=N; Ts=T; xp=0; y=0; yip=0; ydp=0;
  setOutLim(1e9,-1e9);
}
void PID::compute(double x)
{
  double yp=kp*x;
  double yi=yip+ki*Ts/2*(x+xp);
  double yd=(kd*Nf*(x-xp)+ydp)/(Nf*Ts+1);
  y=yp+yi+yd;
  if(y>=outMax)
  {
    y=outMax;
  }
  if(y<=outMin)
  {
    y=outMin;
  }
  xp=x;
  yip=yi; ydp=yd;
}
double PID::output()
{
  return y;
}
void PID::setOutLim(double ma,double mi)
{
  if(ma<mi)return;
  outMax=ma; outMin=mi;
}
void PID::setSampleTime(double T)
{
  Ts=T;
}
void PID::setTune(double P,double I,double D,double N)
{
 kp=P; ki=I>=0?I:ki; kd=D>=0?D:kd; Nf=N>0?N:Nf; 
}
void PID::reset()
{
  xp=0; y=0; yip=0; ydp=0;
}
