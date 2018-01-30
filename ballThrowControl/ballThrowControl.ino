#include <Servo.h>
Servo Servo1;
Servo Servo2;

boolean TRUE=1;
boolean FALSE=0;
const int FWD=1;
const int REV=-1;
const int OFF=0;

const int mixerWhite = 12;
const int mixerRed = 11;
const int conveyorWhite = 4;
const int conveyorRed = 5;
const int servo1Pin = 10;
const int servo2Pin = 9;
const int startSwitch = 3;
// ---------------------------------------------------
void setup() {
  // put your setup code here, to run once:

  Servo1.attach(servo1Pin);
  Servo2.attach(servo2Pin);
  
  pinMode(mixerRed, OUTPUT);
  pinMode(mixerWhite, OUTPUT);
  pinMode(conveyorRed, OUTPUT);
  pinMode(conveyorWhite, OUTPUT);
  pinMode(startSwitch, INPUT);

  mixerRelay(OFF);   // connect mixer to relay1
  conveyorRelay(OFF);   // connect conveyor to relay2
  servo1Speed(FWD,0);
  servo2Speed(FWD, 0);

  int switchState = 0;
  int shooterSpeed = 100;
  int shooterDirection = REV;
}
// ----------------------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:

  // read the input switch and use it to start
  int switchState = digitalRead(startSwitch);
  if(switchState = TRUE) {

    // reverse the throwing wheel and conveyor
    mixerRelay(OFF);
    conveyorRelay(REV);
    servo1Speed(REV, 100);
    delay(500);
    // take a quick break
    conveyorRelay(OFF);
    servo1Speed(FWD, 0);
    delay(50);
    // start loading and shooting
    mixerRelay(FWD);
    conveyorRelay(FWD);
    servo1Speed(FWD, 100);
    delay(15*1000);
    
  }
delay(10);
}

// ------------------------------------------------------------
void servo1Speed(int DIR, int percent) {
  int val=map(percent, 0, 100, 0, 700);
  Servo1.writeMicroseconds(1500 + (DIR*val));
}

void servo2Speed(int DIR, int percent){
   int val=map(percent, 0, 100, 0, 700);
   Servo1.writeMicroseconds(1500+ (DIR*val));
}

void mixerRelay(int setting) {
  switch(setting) {
    case OFF:
      digitalWrite(mixerWhite, LOW);
      digitalWrite(mixerRed, LOW);
    break;

    case FWD:
      digitalWrite(mixerWhite, HIGH);
      digitalWrite(mixerRed, LOW);
    break;

    case REV:
      digitalWrite(mixerWhite, LOW);
      digitalWrite(mixerRed, HIGH);
    break;

    default:
      digitalWrite(mixerWhite, LOW);
      digitalWrite(mixerRed, LOW);
    break;
  }
}

void conveyorRelay(int setting) {
  switch(setting) {
    case OFF:
      digitalWrite(conveyorWhite, LOW);
      digitalWrite(conveyorRed, LOW);
    break;

    case FWD:
      digitalWrite(conveyorWhite, HIGH);
      digitalWrite(conveyorRed, LOW);
    break;

    case REV:
      digitalWrite(conveyorWhite, LOW);
      digitalWrite(conveyorRed, HIGH);
    break;

    default:
      digitalWrite(conveyorWhite, LOW);
      digitalWrite(conveyorRed, LOW);
    break;
  }
}
