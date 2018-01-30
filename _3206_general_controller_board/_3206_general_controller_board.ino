/*  This is the basic code for setting up and running 
    the TEAM 3206 Basic Robot Controller. 
    
    Inputs:
    2 - Potentiometers for speed input
    2 - Normally Open push button switches with pulldowns 
    1 - 3 position slide switch FWD, OFF, REV
    
    Outputs
    4 - PWM outputs for motor controllers or servos
    1 - Spike Relay Output (3 Wire)     */

#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
        
int servo1val;
int servo2val;
int servo3val;
int servo4val;
        
const int servo1Pin=11;
const int servo2Pin=10;
const int servo3Pin=9;
const int servo4Pin=6;

const int switch1Pin=2;
int switch1;
const int switch2Pin=3;
int switch2;
const int slideswitch3Pin = 4;
int switch3;
const int slideswitch4Pin = 5;
int switch4;
int relayval;

const int ledPin = 13;

const int relay1Red = 0;
const int relay1White = 1;
const int relay2Red = 7;
const int relay2White = 8;

const int pot1 = 0;
const int pot2 = 2;

int pot1Analog;
int pot2Analog;



void setup() {
  // put your setup code here, to run once:

  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);
  servo4.attach(servo4Pin);

  pinMode(ledPin, OUTPUT);
  pinMode(relay1Red, OUTPUT);
  pinMode(relay1White, OUTPUT);
  pinMode(relay2Red, OUTPUT);
  pinMode(relay2White, OUTPUT);  
  
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);
  pinMode(slideswitch3Pin, INPUT);
  pinMode(slideswitch4Pin, INPUT);
  
  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
  // read the inputs
  pot1Analog = analogRead(pot1);    // reads between 0 and 1023
  pot2Analog = analogRead(pot2); 
  
  servo1val = map(pot1Analog, 0, 1023, 700, 2200);
  servo1.writeMicroseconds(servo1val);
  
  switch1 = digitalRead(switch1Pin);
  switch2 = digitalRead(switch2Pin);
  
  switch3 = digitalRead(slideswitch3Pin);
  switch4 = digitalRead(slideswitch4Pin);  
  relayval = switch4 + 2*switch3;
  setSpike1(relayval);
  
}

void setSpike1(int val){ 
  /*  The Spike Relay uses two optoisolated inputs for control
      The Red and White PWM cable is the interface
      Truth Table
      Red   White   M+    M-
      0     0       0V    0V               Case 0 & Default
      0     1       12V   0V     Forward   Case 1
      1     0       0V    12V    Reverse   Case 2
      1     1       12V   12V              Case 3         */
      
      switch (val){
        case 0:
          digitalWrite(relay1Red, LOW);
          digitalWrite(relay1White, LOW);
        break;
        
        case 1:
          digitalWrite(relay1Red, LOW);
          digitalWrite(relay1White, HIGH);        
        break;
        
        case 2:
          digitalWrite(relay1Red, HIGH);
          digitalWrite(relay1White, LOW);        
        break;
        
        case 3:
          digitalWrite(relay1Red, HIGH);
          digitalWrite(relay1White, HIGH);        
        break;
        
        default:
          digitalWrite(relay1Red, LOW);
          digitalWrite(relay1White, LOW);       
        break;  
      }  
}
