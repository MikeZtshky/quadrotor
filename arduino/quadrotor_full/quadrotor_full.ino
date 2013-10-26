/****************************************************
* Basic Quadrotor Motor Control
* Hayk Martirosyan
****************************************************/

#include "Timer.h"
#include "Servo.h"
#include <SoftwareSerial.h>
#include "constants.h"
#include "command_parser.h"
#include "motor_driver.h"
#include "accelerometer.h"

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

void parse_commands() {
  CMD_commands();
  MDR_commands();
  ACC_commands();
}

void setup() { 
  
  Serial.begin(9600);
  
  CMD_init(&t);
  MDR_init(&t);
  ACC_init(&t);
  
  delay(1000);
  
  Serial.println("");
  Serial.println("Quadrotor initialized!");
  
  t.every(CMD_UPDATE_RATE, parse_commands);
}

void loop() {
  
  t.update();
} 

