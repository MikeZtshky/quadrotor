/****************************************************
* Bluetooth Module
* Module:BLU
* Hayk Martirosyan
****************************************************/

#include "bluetooth.h"

// --------------------------------------------------
// PRIVATE CONSTANTS
// --------------------------------------------------

#define BLUETOOTH_RX 4
#define BLUETOOTH_TX 5

#define BLUESMIRF_BAUD 9600

#define END_COMMAND '\r'
#define DELIMITER ' '

#define READ_COUNT 5

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

SoftwareSerial bluesmirf(BLUETOOTH_RX, BLUETOOTH_TX);

String bluesmirf_rx_buffer = "";

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

void BLU_send_command(String command, int arg) {
  Serial.println("Command sent over bluetoth: " + command + ", arg: " + String(arg));
  bluesmirf.print(command);
  bluesmirf.print(DELIMITER);
  bluesmirf.print(arg);
  bluesmirf.print(END_COMMAND);
}

void BLU_send_command(String command) {
  //Serial.println("Command sent over bluetooth: " + command);
  bluesmirf.print(command);
  bluesmirf.print(END_COMMAND);
}

void BLU_parse_command(String command) {
  //Serial.println("Command received over bluetooth: " + command);
  
  int delimiter_index = command.indexOf(DELIMITER);
  if(delimiter_index != -1) {
    String command_name = command.substring(0, delimiter_index);
    String arg_str = command.substring(delimiter_index+1);
      int arg = arg_str.toInt();
      if ((arg == 0) && (arg_str != "0"))
        Serial.println("Integer argument converted to zero, ignoring!!");
      else
        CMD_command_received(command_name, arg);
  } else {
    CMD_command_received(command);
  }
}

void BLU_update() {
  
  int i = READ_COUNT;
  while(bluesmirf.available() && (i > 0)) {
    bluesmirf_rx_buffer = bluesmirf_rx_buffer + String((char)bluesmirf.read());
    //Serial.println("Bluesmirf buffer increased: " + bluesmirf_rx_buffer);
    
    int end_command_index = bluesmirf_rx_buffer.indexOf(END_COMMAND);
    
    if(end_command_index != -1) {
      String command = bluesmirf_rx_buffer.substring(0, end_command_index);
      bluesmirf_rx_buffer = bluesmirf_rx_buffer.substring(end_command_index+1);
      BLU_parse_command(command);
    }
    i--;
  }

}

void BLU_init(Timer* t) {
  
  bluesmirf.begin(BLUESMIRF_BAUD);
  
  t->every(BLU_UPDATE_RATE, BLU_update);
}

void BLU_commands() {
  
  // Commands
}

