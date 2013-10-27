/****************************************************
* Bluetooth Module
* Module:BLU
* Hayk Martirosyan
****************************************************/

#ifndef BLUETOOTH_H
#define	BLUETOOTH_H

#include "Arduino.h"
#include "Timer.h"
#include <SoftwareSerial.h>

#include "constants.h"
#include "command_parser.h"

// --------------------------------------------------
// PUBLIC CONSTANTS
// --------------------------------------------------

#define BLU_UPDATE_RATE 2

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void BLU_init(Timer* t);
void BLU_commands();

void BLU_send_command(String command);
void BLU_send_command(String command, int arg);

#endif	/* BLUETOOTH_H */

