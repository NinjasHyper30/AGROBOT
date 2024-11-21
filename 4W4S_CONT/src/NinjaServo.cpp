#include "NinjaServo.h"
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
static bool timerSetup=false;
NinjaServo::NinjaServo()
:compReg(nullptr),microSec(DEFAULT_PULSE_WIDTH),sPin(150)
{
}
void NinjaServo::attach(byte pin)
{
    if(!timerSetup)
    {
        //initialize the timers for 50hz
        TCCR3A=B00000010;
        TCCR3B=B10111010;
        TCCR5A=B00000010;
        TCCR5B=B10111010;
        ICR5=40000;
        ICR3=40000;
        timerSetup=true;
    }
    if(compReg)return;
    pinMode(pin,OUTPUT);
    sPin=pin;
    switch (digitalPinToTimer(pin))
    {
    case NOT_ON_TIMER:
        break;
    case TIMER3A:
    {
        sbi(TCCR3A,COM3A1);
        compReg=&OCR3A;
        break;
    }
    case TIMER3B:
    {
        sbi(TCCR3A,COM3B1);
        compReg=&OCR3B;
        
        break;   
    }
    case TIMER3C:
    {
        sbi(TCCR3A,COM3C1);
        compReg=&OCR3C;
        break;
    }
    case TIMER5A:
    {
        sbi(TCCR5A,COM5A1);
        compReg=&OCR5A;
        break;
    }
    case TIMER5B:
    {
        sbi(TCCR5A,COM5B1);
        compReg=&OCR5B;
        
        break;   
    }
    case TIMER5C:
    {
        sbi(TCCR5A,COM5C1);
        compReg=&OCR5C;
        break;
    }
    default:
        break;
    }
    this->writeMicroseconds(microSec);
}
bool NinjaServo::writeMicroseconds(int micSec)
{
    if(micSec>MAX_PULSE_WIDTH||microSec<MIN_PULSE_WIDTH)return false;
    microSec=micSec;
    if(!compReg)return false;
    *compReg=(2*micSec);    //1 count = 0.5microsec
    return true;
}
bool NinjaServo::write(int angle)
{
    if(abs(angle)>90)return false;
    int micr=map(angle,-90,90,MIN_PULSE_WIDTH,MAX_PULSE_WIDTH);
    return writeMicroseconds(micr);
}
int NinjaServo::read()
{
    int angle=map(microSec,MIN_PULSE_WIDTH,MAX_PULSE_WIDTH,-90,90);
    return angle;
}
unsigned int NinjaServo::readMicroseconds()
{
    return microSec;
}
NinjaServo::~NinjaServo()
{
    digitalWrite(sPin,LOW);
}
