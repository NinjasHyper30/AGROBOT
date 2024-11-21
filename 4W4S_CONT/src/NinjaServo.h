#include "Arduino.h"
#ifndef _NINJA_SERVO
#define _NINJA_SERVO
#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
//Supports only on MEGA and pwm pins of timer 3 and 5
// max six servos
class NinjaServo
{
private:
    volatile uint16_t* compReg;  //output compare register OCR
    unsigned int microSec;       
    byte sPin;                   //Servo attached pin
public:
    NinjaServo();
    void attach(byte pin);       //attach servopin
    bool write(int angle);       
    bool writeMicroseconds(int micSec);      //provide pulse width in microSecs
    int read();                              //cur position
    unsigned int readMicroseconds();        
    ~NinjaServo();
};

#endif

