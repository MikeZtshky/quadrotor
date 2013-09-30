
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
// FUNCTIONS
// --------------------------------------------------

// --------------------------------------------------
// MAIN FUNCTIONS
// --------------------------------------------------

void setup() 
{ 
  
  Serial.begin(9600);
  
  CMD_init();
  MDR_init();
  
  // Update each module
  t.every(CMD_UPDATE_RATE, CMD_update);
  t.every(MDR_UPDATE_RATE, MDR_update);
  
  // Parse each module's commands
  t.every(CMD_UPDATE_RATE, MDR_commands);
  
  t.every(1000, MDR_print_position);
}

void loop() {
  

  
  //servo1.writeMicroseconds(int(pos));
  t.update();
} 

