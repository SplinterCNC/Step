/*
  Step.cpp - Library for stepper motors.
  Created by Rian van vuuren, June, 2016.
  Released into the public domain.
*/

/*

       Project: S curve
      Language: Arduino r12
          Date: January 2008
        Author: C. Eckert

*/

#include "Arduino.h"
#include "Step.h"

Motor::Motor(int StepPin,int DirPin)

{
  pinMode (StepPin, OUTPUT);
  _StepPin = StepPin;
   
   pinMode(DirPin, OUTPUT);
  _DirPin = DirPin;
 
}





void  Motor::Step(int steps, int speed,long accelup, long acceldown)
{

{

this->steps = steps;
this->speed = speed;
this->accelup = accelup;
this->acceldown = acceldown;

}


long up = accelup;     // acceleration time (microsec)
long dwn = acceldown;     // decelleration time (microsec)

long ta = up;     // acceleration time (microsec)
long td = dwn;     // decelleration time (microsec)
long t = td/9;       // current time (microsec)  -  You need to seed the initial time with something > 0
                     //                             so you don't calculate to long of a delay

long dly;           // stepper pulse delay (microsec)
long t12;           // time during constant velocity (microsec)

int count = 0;      // count the number of pulses
int Perr = 0;       // error in position

int var = 0;

while(var < 1){ 



t12 = (steps/(speed/1e6))-0.5*(ta+td);

 // Decide which part of the velocity curve your at
 if (t<ta) {                                       // Acceleration
   //Serial.println ("Acceleration Curve");
   dly = (ta)/(2*(speed/1e6)*t);
 } 
 else if (t>=ta && t<(ta+t12)){                    // Constant velocity
   //Serial.println ("Constant Velocity");
   dly = 1/(2*(speed/1e6));
 }
 else if (t>=(ta+t12) && t<(ta+t12+td)){          // Deceleration
   //Serial.println ("Deceleration Curve");
   dly = 1/(2*((speed/1e6)-(speed/(1e6*td))*(t-ta-t12)));
 }
 
 t = t+2*dly; // update the current time
 
 
 // Move stepper one pulse using delay just calculated
 digitalWrite(_StepPin, HIGH);
 delayMicroseconds(dly);
 digitalWrite(_StepPin, LOW);
 delayMicroseconds(dly);
 count ++;
   
 // The move is finished
 if (t>(ta+t12+td)){
   
   
   // Correct for any position error due to rounding
   Perr = steps-count;
   if (Perr < 0) {
    
     Perr = -1*Perr;
   }
   for (;Perr>0;){
     digitalWrite(_StepPin, LOW);
     delayMicroseconds(dly);
     digitalWrite(_StepPin, LOW);
     delayMicroseconds(dly);
     Perr--;
   }
   
   count=0;
   t=td/9;
   
 var++; 
 }
 
}
}
    

void Motor::Stop()
{
  digitalWrite(_StepPin, LOW);
   
}


void Motor::DirPos()
{
  
   digitalWrite(_DirPin, HIGH);
  
}

void Motor::DirNeg()
{
  
   digitalWrite(_DirPin, LOW);
  
}

void  Motor::ConSpeed(int speed)
{

{


this->speed = speed;

}




long steps = 2000;

long ta = 0;     // acceleration time (microsec)
long td = 0;     // decelleration time (microsec)
long t = td/9;       // current time (microsec)  -  You need to seed the initial time with something > 0
                     //                             so you don't calculate to long of a delay

long dly;           // stepper pulse delay (microsec)
long t12;           // time during constant velocity (microsec)

int count = 0;      // count the number of pulses
int Perr = 0;       // error in position

//int var = 0;

//while(var < )
 



t12 = (steps/(speed/1e6))-0.5*(ta+td);

 // Decide which part of the velocity curve your at
 if (t<ta) {                                       // Acceleration
   //Serial.println ("Acceleration Curve");
   dly = (ta)/(2*(speed/1e6)*t);
 } 
 else if (t>=ta && t<(ta+t12)){                    // Constant velocity
   //Serial.println ("Constant Velocity");
   dly = 1/(2*(speed/1e6));
 }
 else if (t>=(ta+t12) && t<(ta+t12+td)){          // Deceleration
   //Serial.println ("Deceleration Curve");
   dly = 1/(2*((speed/1e6)-(speed/(1e6*td))*(t-ta-t12)));
 }
 
 t = t+2*dly; // update the current time
 
 
 // Move stepper one pulse using delay just calculated
 digitalWrite(_StepPin, HIGH);
 delayMicroseconds(dly);
 digitalWrite(_StepPin, LOW);
 delayMicroseconds(dly);
 count ++;
   
 // The move is finished
 if (t>(ta+t12+td)){
   
   
   // Correct for any position error due to rounding
   Perr = steps-count;
   if (Perr < 0) {
    
     Perr = -1*Perr;
   }
   for (;Perr>0;){
     digitalWrite(_StepPin, LOW);
     delayMicroseconds(dly);
     digitalWrite(_StepPin, LOW);
     delayMicroseconds(dly);
     Perr--;
   }
   
   count=0;
   t=td/9;
   
 //var++; 
 }
 
}






