/* Controller Board for 1st Robotics
 * Mark Gryzwa Nov 2018
 * 
 * 2 Servo Motors
 * 1x LCD Feedback
 * 
 */


/* connections
 * A0 - Potentiometer 1
 * A1 - Potentiometer 2
 * A4 - SDA for LCD
 * A5 - SCL for LCD
 * 
 * D0 - Reserved
 * D1 - Reserved
 * D2 - Push button 1
 * D3 - Push button 2
 * 
 * D6 - Servo 1
 * D9 - Servo 2
 * 
 * D13 - LED Reserved
 */

// setup LCD
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  LiquidCrystal_I2C lcd(0x3f,20,4);

// setup Servo
  #include <Servo.h>
  Servo servo1;
  Servo servo2;

// analog pins
#define pot1pin 0
#define pot2pin 1

//digital pins
#define servo1pin 6
#define servo2pin 9
#define button1   2
#define button2   3

#define rev 700    // microsecond offsets for servo
#define fwd 700

  // global variables
  int pot1val_current = 0;
  int pot1val_new = 0;
  int pot2val_current = 0;
  int pot2val_new = 0;
  int servo1_percent = 0;
  int servo1_val = 0;
  int servo2_percent = 0;
  int servo2_val = 0;
  
  int button1_current = 0;
  int button1_new = 0;
  int button2_current = 0;
  int button2_new = 0;

void setup() {
  // --------------------------- LCD
  lcd.init();
  lcd.backlight();
  lcd.clear(); 
  // --------------------------- Servo
  servo1.attach(servo1pin);
  servo2.attach(servo2pin);
  // -------------------------- pin assignments
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);  
}

void loop() {

  // analog reads
    pot1val_new = analogRead(pot1pin);
      servo1_percent = map(pot1val_new, 0, 1024, -100, 100);
      servo1_val = map(pot1val_new, 0, 1024, 1500-rev, 1500+fwd);
    pot2val_new = analogRead(pot2pin);
      servo2_percent = map(pot2val_new, 0, 1024, -100, 100);
      servo2_val = map(pot2val_new, 0, 1024, 1500-rev, 1500+fwd);

    //update lcd for servos
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("SV1=");
    lcd.print(servo1_percent);
    lcd.setCursor(0,1);
    lcd.print("SV2=");
    lcd.print(servo2_percent);
    lcd.setCursor(11,0);
    lcd.print("B1234");  
    
    
  // digital reads
    button1_new = digitalRead(button1);
    button2_new = digitalRead(button2);

  // did button1 change state   
    if(button1_new != button1_current) {
      //button changed state
      button1_current = button1_new;
      if(button1_current == 1){
          servo1.writeMicroseconds(servo1_val);
          lcd.setCursor(9,0);
          lcd.print("1");
          lcd.setCursor(12,1);
          lcd.print("1");
      }
      else {
         servo1.writeMicroseconds(1500);
         lcd.setCursor(9,0);
         lcd.print("0");
         lcd.setCursor(12,1);
         lcd.print("0");
      }
    }

  // did button2 change state   
    if(button2_new != button2_current) {
      //button changed state
      button2_current = button2_new;
      if(button2_current == 1){
          servo2.writeMicroseconds(servo2_val);
          lcd.setCursor(9,1);
          lcd.print("1");
          lcd.setCursor(13,1);
          lcd.print("1");
      }
      else {
         servo1.writeMicroseconds(1500);
         lcd.setCursor(9,1);
         lcd.print("0");
         lcd.setCursor(13,1);
         lcd.print("0");
      }
    }
    
   delay(50);
}
