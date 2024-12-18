#include <TimerOne.h>
#include <math.h>
#include "src/motorController.h"
#include "src/NinjaServo.h"


#define Vm 9.0
#define DSO 32
//defining constants
float Vdc=Vm-1.7; 
double kw=3468.6; //encoder costant
float Ts=0.05; //sampling time

volatile double w[4];   //current value of wheel speed
volatile double wRef[4];   //driving angles
volatile int delta[4];    //steerMotor angles

volatile bool state=true;
float Vx,Vy,gam;  //required speed of the BOT
float x=0,y=0,phi=0;
float ld;         //half of track
float lf;       
float lr;      //wheel base lf+lr
float R=0.05;       //radius of wheel
void MC_ISR();
void getRoverSpeed();
void getOmega();

//                  Vdc,pwmpin,dir,enca,encb,kw,Ts,kp,ki,kd,N
motorConfig config1={Vdc,6,25,2,33,kw,Ts,0.3069,16.67,0,1e7};
motorConfig config2={Vdc,7,27,3,35,kw,Ts,0.3069,16.67,0,1e7};
motorConfig config3={Vdc,8,29,18,37,kw,Ts,0.3069,16.67,0,1e7};
motorConfig config4={Vdc,9,31,19,39,kw,Ts,0.3069,16.67,0,1e7};

//initializing driving motors
motorController driverMotor[4]={motorController(config1),motorController(config2),
                        motorController(config3),motorController(config4)};
NinjaServo steerMotor[4]; 

void setup()
{
  // initializing timers for pwm freq
  TCCR2B = TCCR2B & B11111000 | B00000001;
  TCCR4B = TCCR4B & B11111000 | B00000001;
  //initializing timer interrupt
  Timer1.initialize(50000);
  Timer1.attachInterrupt(MC_ISR);
  Serial.begin(9600);
  //initializing sttering motors
  steerMotor[0].attach(5);
  steerMotor[1].attach(44);
  steerMotor[2].attach(45);
  steerMotor[3].attach(46);
  // pinMode(DSO,OUTPUT);
}

void loop() 
{
  if(state)
  {
    cli();
    // digitalWrite(DSO,HIGH);
    getOmega();
    state=false;
    // digitalWrite(DSO,LOW);
    sei();    
  }
}
