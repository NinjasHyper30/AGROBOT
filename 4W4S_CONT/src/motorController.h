#ifndef motorCont_
#define motorCont_

#include "Arduino.h"
#include "pid.h"
#include "quadEncoder.h"
#include "HB.h"

struct motorConfig
{
    //Hbridge const
    float V;           //max voltage
    byte pwmPin;         //hbridge pwm pin
    byte dirPin;         //hbridge directional pin
    //encoder const
    byte encA;           //encoder channel A
    byte encB;           //encoder channel B
    double wc;           //encoder speed const
    //compensator const
    double Ts;           //sampling time
    double kp;           //propotional gain
    double ki;           //integeral
    double kd;           //derivative
    double N;            //filter cutoff
};


class motorController
{
private:
    PID cont;
    qEncoder encoder;
    HB chop;
    float Vm;     //input dc voltage
public:
    motorController(motorConfig &config);
    motorController(float Vm,byte encA,byte encB,byte wc,HB &cov,PID &comp);
    double setSpeed(double speed);
    void reset();
    void changeGains(double P,double I=-1,double D=-1,double N=-1,double T=-1);
    void changeGains(motorConfig &config);
};

#endif