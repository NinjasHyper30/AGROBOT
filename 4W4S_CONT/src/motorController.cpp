#include "motorController.h"

motorController::motorController(motorConfig &config)
:Vm(config.V),chop(config.pwmPin,config.dirPin),encoder(config.encA,config.encB,config.wc),
cont(config.Ts,config.kp,config.ki,config.kd,config.N)
{
    cont.setOutLim(Vm,-Vm);
}

motorController::motorController(float V,byte encA,byte encB,byte wc,HB &cov,PID &comp)
:Vm(V),encoder(encA,encB,wc),chop(cov),cont(comp)
{
    cont.setOutLim(Vm,-Vm);
}

void motorController::reset()
{
    cont.reset();
    chop.drive(0);
}
double motorController::setSpeed(double w0)
{
    double w=encoder.getSpeed();
    double e=(w0-w);
    cont.compute(e);
    double out=cont.output();
    int dc=((out/Vm)*255);
    chop.drive(dc);
    return w;
}
void motorController::changeGains(double P,double I,double D,double N,double T)
{
    cont.setTune(P,I,D,N);
    if(T>0)cont.setSampleTime(T);
}
 void motorController::changeGains(motorConfig &config)
 {
    this->changeGains(config.kp,config.ki,config.kd,config.N,config.Ts);
 }