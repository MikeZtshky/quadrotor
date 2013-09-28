// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 

  for(pos = 0; pos < 50; pos++) {                                
    myservo.write(pos);
    delay(150);
  }
  for(pos = 50; pos >= 0; pos--) {                                
    myservo.write(pos);
    delay(150);
  }
 
 myservo.write(0); 
} 
