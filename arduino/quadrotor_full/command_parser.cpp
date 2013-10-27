/****************************************************
* Serial Command Parser
* Module: CMD
* Hayk Martirosyan
****************************************************/

#include "command_parser.h"
#include "motor_driver.h"
#include "accelerometer.h"
#include "usb_serial.h"

// --------------------------------------------------
// PRIVATE CONSTANTS
// --------------------------------------------------

#define NO_ARGUMENT -3333

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

String last_command = String();
int last_arg = -1;

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

static int CMD_check_command_string(String* pStr) {
  
  String command = *pStr;
  
  if (command == last_command)
    return TRUE;
  return FALSE;
}

static void CMD_update() {
  
}

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void CMD_check_command(String pCommand, void (*callback)(void)) {
  
  if(last_arg != NO_ARGUMENT) {
    //Serial.println("Ignoring command, argument present!");
    return;
  }
  
  if(CMD_check_command_string(&pCommand))
    callback();
}

void CMD_check_command(String pCommand, void (*callback)(int)) {
  
  if(last_arg == NO_ARGUMENT) {
    return;
  }
  
  if(CMD_check_command_string(&pCommand))
    callback(last_arg);
}

void check_all_commands() {
  BLU_commands();
  SER_commands();
  CMD_commands();
  MDR_commands();
  ACC_commands();
}

void CMD_command_received(String command) {
  Serial.println("CMD command received: " + command);
  last_command = command;
  last_command.toUpperCase();
  last_arg = NO_ARGUMENT;
  check_all_commands();
}

void CMD_command_received(String command, int arg) {
  Serial.println("CMD command received: " + command + ", arg: " + String(arg));
  last_command = command;
  last_command.toUpperCase();
  last_arg = arg;
  check_all_commands();
}

void CMD_init(Timer* t) {

  t->every(CMD_UPDATE_RATE, CMD_update);
}

void CMD_test() {
  Serial.println("Test command received!");
}

void CMD_test2(int arg) {
  Serial.print("Test command received with arg: ");
  Serial.println(arg);
}

void CMD_commands() {
  CMD_check_command("CMD_test", CMD_test);
  CMD_check_command("CMD_test2", CMD_test2);
}

