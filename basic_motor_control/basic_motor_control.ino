
/****************************************************
* Basic Quadrotor Motor Control
* Hayk Martirosyan
****************************************************/


#include "Timer.h"
#include "Servo.h"

#include "constants.h"
#include "command_parser.h"
#include "motor_driver.h"

// --------------------------------------------------
// CONSTANTS
// --------------------------------------------------

// --------------------------------------------------
// VARIABLES
// --------------------------------------------------

Timer t;

// --------------------------------------------------
// METHODS
// --------------------------------------------------

void setup() 
{ 
  
  Serial.begin(9600);
  
  CMD_init(&t);
  MDR_init(&t);
  
  delay(2000);
  
  Serial.println("");
  Serial.println("Quadrotor initialized!");
}

void loop() {
  
  t.update();
} 

