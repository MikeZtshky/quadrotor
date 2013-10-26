/****************************************************
* Serial Command Parser
* Module: CMD
* Hayk Martirosyan
****************************************************/

#include "command_parser.h"

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

static String serial_received = String();

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

static int CMD_new_serial_data() {
  if (serial_received.length() > 0)
    return TRUE;
  return FALSE;
}

static void CMD_read_serial() {
  
  serial_received = String();
  
  if (Serial.available()) {
    
    while(Serial.available())
      serial_received += (char)Serial.read();
    
    Serial.print("Received: ");
    Serial.println(serial_received);
  }
}

static int CMD_check_command_string(String* pStr) {
  
  // No new data
  if (!CMD_new_serial_data())
    return FALSE;
  
  String command = *pStr;
  
  // Serial received is too short to be this command
  if (serial_received.length() < command.length())
    return FALSE;
  
  // Make sure all the characters match up
  int i;
  for(i = 0; i < command.length(); i++) {
     if(serial_received[i] != command[i])
         return FALSE;
  }
  
  // Make sure if there are more characters, that the next one is a space
  if (serial_received.length() > command.length())
    if (serial_received[command.length()] != CMD_DELIMITER)
      return FALSE;
  
  // Matched up
  return TRUE;
}

static void CMD_update() {
  
  // Update serial_received
  CMD_read_serial();
}

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void CMD_init(Timer* t) {
  
  t->every(CMD_UPDATE_RATE, CMD_update);
}

void CMD_check_command(String pCommand, void (*callback)(void)) {
  
  
  if(CMD_check_command_string(&pCommand))
    callback();
   
}

void CMD_test() {
  Serial.println("Test command received!");
  
  // SOFTWARE RESET
  void(* resetFunc) (void) = 0;
  resetFunc();
}

void CMD_commands() {
  
}


