/****************************************************
* USB Serial Module
* Module:SER
* Hayk Martirosyan
****************************************************/

#include "usb_serial.h"
#include <stdlib.h>

// --------------------------------------------------
// PRIVATE CONSTANTS
// --------------------------------------------------

#define USB_SERIAL_BAUD 9600

#define END_COMMAND '\r'
#define DELIMITER ' '

#define READ_COUNT 5

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

String usb_serial_rx_buffer = "";

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

void SER_send_command(String command) {
  Serial.println("Command sent to USB serial: " + command);
}

void SER_parse_command(String command) {
  Serial.println("Command received over USB serial: " + command);
  
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

void SER_update() {
  
  int i = READ_COUNT;
  while(Serial.available() && (i > 0)) {
    usb_serial_rx_buffer = usb_serial_rx_buffer + String((char)Serial.read());
    //Serial.println("USB serial buffer increased: " + usb_serial_rx_buffer);
    
    int end_command_index = usb_serial_rx_buffer.indexOf(END_COMMAND);
    
    if(end_command_index != -1) {
      String command = usb_serial_rx_buffer.substring(0, end_command_index);
      usb_serial_rx_buffer = usb_serial_rx_buffer.substring(end_command_index+1);
      SER_parse_command(command);
    }
    i--;
  }
}

void SER_init(Timer* t) {
  
  Serial.begin(USB_SERIAL_BAUD);
  
  t->every(SER_UPDATE_RATE, SER_update);
}

void SER_commands() {
  
  // Commands
}

