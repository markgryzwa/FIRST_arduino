/*
This our light show for the 2015 robot.  Listens via a microphone and outputs via tri color led based on volume envelope.

 
*/



int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int peak_value = 0;
int dc_value = 0;
int level;

int red=13;                // output pin for red
int blue=11;               // output pin for blue
int green=9;               // output pin for green

int first_run = 0;        // count the first time loop gets executed.  Don't run this after that.

 
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);


}

void loop() {
  
  // run a quick color check prior to running the normal loop
  
  if(first_run == 0){
    
    // RED
    writeDigital(red, HIGH);
    writeDigtial(green, LOW);
    writeDigital(blue, LOW);
    delay(2000);
   
    //  GREEN 
    writeDigital(red, LOW);
    writeDigtial(green, HIGH);
    writeDigital(blue, LOW);
    delay(2000);   
    
    
    // BLUE
    writeDigital(red, LOW);
    writeDigtial(green, LOW);
    writeDigital(blue, HIGH);
    delay(2000);
    
    // ORANGE
    writeDigital(red, HIGH);
    writeDigtial(green, HIGH);
    writeDigital(blue, LOW);
    delay(2000);
    
    // 
    writeDigital(red, HIGH);
    writeDigtial(green, LOW);
    writeDigital(blue, HIGH);
    delay(2000);
    
    // YELLOW
    writeDigital(red, LOW);
    writeDigtial(green, HIGH);
    writeDigital(blue, HIGH);
    delay(2000);
    
    // WHITE
    writeDigital(red, HIGH);
    writeDigtial(green, HIGH);
    writeDigital(blue, HIGH);
    delay(2000);
    
    writeDigital(red, LOW);
    writeDigtial(green, LOW);
    writeDigital(blue, LOW);
    delay(2000);
    
   first_run = 1; 
  }
  
  
  
  int c = 0;
  peak_value = 0;
  
  
  while (c<10){
    sensorValue = analogRead(analogInPin);
    dc_value = sensorValue - 512;
    dc_value = abs(dc_value);
    peak_value = max(peak_value, dc_value);
    c++;
    delay(2);
  }
  
  level = peak_value / 72;
  
  switch (level ) {
    case 0:
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    break;
    
    case 1:
    digitalWrite(red, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    break;
    
    case 2:
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    break;
    
    case 3:
    digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    break;
    
    case 4:
    digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    break;
    
    case 5:
    digitalWrite(red, HIGH);
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    break;
    
    case 6:
    digitalWrite(red, LOW);
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
    break;
    
    case 7:
    digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    digitalWrite(green, HIGH);
    break;
       
    default:
    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
  }
  //if(peak_value > 300){
    //analogWrite(analogOutPin, 255);
    //digitalWrite(13, HIGH);
    //outputValue = 255;
  //}
  //else {
    //analogWrite(analogOutPin, 0);
  //  digitalWrite(13, LOW);
  //  outputValue = 0;
  //}
  
  // outputValue = map(sensorValue, 0, 1023, 0, 255);  
  // change the analog out value:
  // analogWrite(analogOutPin, outputValue);           

  // print the results to the serial monitor:
  Serial.print("Peak = " );                       
  Serial.print(peak_value);      
  Serial.print("\t level = ");      
  Serial.println(level);   

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(30);                     
}
