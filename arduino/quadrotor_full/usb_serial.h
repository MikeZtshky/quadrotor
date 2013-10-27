/****************************************************
* Serial Module
* Module:SER
* Hayk Martirosyan
****************************************************/

#ifndef USB_SERIAL_H
#define	USB_SERIAL_H

#include "Arduino.h"
#include "Timer.h"

#include "constants.h"
#include "command_parser.h"

// --------------------------------------------------
// PUBLIC CONSTANTS
// --------------------------------------------------

#define SER_UPDATE_RATE 2

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void SER_init(Timer* t);
void SER_commands();

void SER_send_command(String command);

#endif	/* USB_SERIAL_H */

