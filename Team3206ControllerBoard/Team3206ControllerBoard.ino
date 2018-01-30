/* 
 Setting up a control board for Team 3206 FIRST Robotics Team
 Royal T Wrecks
 
 Two Motor Controllers
    - Speed control with a knob (potentiometer)
 One Relay
    - Controlled by switch
 One Limit Switch 
 
*/

#include <Servo.h> 
 
Servo motor1;  // create servo object to control a servo 
Servo motor2;  // 2nd motor controller
 
int potpin = 0;  // analog pin used to connect the potentiometer
int val;        // variable to read the value from the analog pin 
int relaySwitch;    // switch for the relay
int limitSwitch;    // limit switch for the motors

const int relaySwitchPin = 0;
const int limitSwitchPin = 12;
const int relayPin1 = 4;
const int relayPin2 = 6;

int fullReverse = 800;
int fullForward = 2200;
int neutral = 1500;

 
void setup() 
{ 
  motor1.attach(3);  // attaches motor controller on pin 9 to the servo object 
  motor2.attach(5); // second motor controller on pin 11
  pinMode(relaySwitchPin, INPUT);
  pinMode(limitSwitchPin, INPUT);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);

} 
 
void loop() 
{ 
  //  read the knob and map it to servo output
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023) 
  val = map(val, 0, 1023, fullReverse, fullForward);     // scale it to use it with the servo (value between 0 and 180) 
  
  //  read the switch states
  relaySwitch = digitalRead(relaySwitchPin);
  limitSwitch = digitalRead(limitSwitchPin);
  
  motor1.writeMicroseconds(1500);       // sets the servo position according to the scaled value 
  
 /* if((limitSwitch == 0) && (val > neutral)) {  // if the limit switch is true do not allow the motor to turn forward
    motor2.writeMicroseconds(neutral);
  }
  else {
    motor2.writeMicroseconds(val);
  } */
 
 while(limitSwitch == 1) {
  motor2.writeMicroseconds(2200);
  limitSwitch=digitalRead(limitSwitchPin);
 }
  delay(100);
  motor2.writeMicroseconds(1600); 
  delay(5000);
  motor2.writeMicroseconds(700);
  delay(1000);
  motor2.writeMicroseconds(1500);
  while(1);                            
} 
