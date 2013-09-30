

#include <Servo.h> 
#include "Timer.h"

// --------------------------------------------------
// CONSTANTS
// --------------------------------------------------

#define SERIAL_BUFFER_SIZE 15

// --------------------------------------------------
// VARIABLES
// --------------------------------------------------

// One servo object per motor stack
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

Timer t;

double pos;
double goal;

String serial_received = String();

// --------------------------------------------------
// FUNCTIONS
// --------------------------------------------------

void print_pos() {
  Serial.print("Position: ");
  Serial.println(servo1.readMicroseconds());
}

void get_serial() {
  
  if (Serial.available()) {
    
    int i;
    for(i = 0; Serial.available(); i++) {
      serial_received[i] = Serial.read();
    }
    serial_received[i] = '\0';
    
    Serial.print("Received: ");
    Serial.println(serial_received);
  }
}

//void check_serial_command(char[] command) {
  //
//1}

void setup() 
{ 
  // Attach the servos to pins
  servo1.attach(11);
  
  pos = 1500;
  goal = 2000;
  
  servo1.writeMicroseconds(int(pos));
  
  Serial.begin(9600);
  t.every(1000, print_pos);
  t.every(100, get_serial); 
}

void loop() 
{ 
  
  
  if (pos < goal)
     pos += .1;
  else if (pos > goal)
     pos -= .1;
  
  servo1.writeMicroseconds(int(pos));
  t.update();
} 
