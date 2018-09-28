/*
  Step.h - Library for stepper motors.
  Created by Rian van vuuren, June, 2016.
  Released into the public domain.
*/

/*

       Project: S curve
      Language: Arduiino r12
          Date: January 2008
        Author: C. Eckert

*/



#ifndef Step_h
#define Step_h

#include "Arduino.h"

class Motor
{
  public:
    Motor(int StepPin, int DirPin);
      
      
    void Step(int steps, int speed, long accelup, long acceldown);
        
    void ConSpeed(int speed2);

    void DirPos();
    void DirNeg();
    void Stop();
    
   
    
    
  private:
    int _StepPin;
    int _DirPin;
    
    int steps;
    int speed;
    int accelup;
    int acceldown;

    int steps2;
    int speed2;
    int accelup2;
    int acceldown2;
    
    
};



#endif
