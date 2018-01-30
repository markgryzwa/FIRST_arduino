
#include <Servo.h>
Servo leftservo;
Servo rightservo;



void setup() {
  // put your setup code here, to run once:
  
  int LEFTPIN = 9;
  int RIGHTPIN = 10;
  
  leftservo.attach(LEFTPIN);      //  left motor control on pin 9
  rightservo.attach(RIGHTPIN);    //  right motor control on pin 10
  
  int LEFT = 0;        // left motor control % (-100 to 100%)
  int RIGHT = 0;      // right motor control % 
 

 


}

void loop() {
  // put your main code here, to run repeatedly: 
  
    motor(100,100);
  delay(2000);
  rightservo.writeMicroseconds(0);
  delay(2000);
  
}



void motor(int LEFT, int RIGHT) {
  //  this sub controls the motor speeds using pwm outputs
  
  int offset = 500;    // the offset needed for full speed
  int STOP = 1500;    // the center of the pwm needed for stop
  
  leftservo.writeMicroseconds(STOP - (LEFT/100)*offset);
  rightservo.writeMicroseconds(STOP + (RIGHT/100)*offset);
}
