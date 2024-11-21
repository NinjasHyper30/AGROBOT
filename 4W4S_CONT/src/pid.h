#include "Arduino.h"

#ifndef pid
#define pid
class PID
{

public:

PID(double T=0,double P=0,double I=0,double D=0,double N=1e7); 
void compute(double x);  

double output();  //obtain the current output

void setOutLim(double ma,double mi);       //set the limits for outputs

void setTune(double P,double I=-1,double D=-1,double N=-1); //changing controller parameters
void reset();                       //resets the controller
void setSampleTime(double T);      //changing sample time

private:
//controller constants
double kp;
double kd;
double ki;
double Nf;  //Filter coefficient
double Ts; //Sampling time
double xp; //previous input
double yip,ydp; //last integral & derivative sample
double y; //output
double outMax,outMin; //maximum ans min output 
};

#endif
