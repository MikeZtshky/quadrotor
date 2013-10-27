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
#include "bluetooth.h"
#include "usb_serial.h"

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

void setup() { 
  
  BLU_init(&t);
  SER_init(&t);
  CMD_init(&t);
  MDR_init(&t);
  ACC_init(&t);
  
  delay(1000);
  
  Serial.println("");
  Serial.println("Quadrotor initialized!");
}

void loop() {
  
  t.update();
} 

