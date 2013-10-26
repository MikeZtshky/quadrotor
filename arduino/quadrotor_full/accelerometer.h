/****************************************************
* Accelerometer Module
* Module:ACC
* Hayk Martirosyan
****************************************************/

#ifndef ACCELEROMETER_H
#define	ACCELEROMETER_H

#include "Arduino.h"
#include "Timer.h"

#include "constants.h"
#include "command_parser.h"

// --------------------------------------------------
// PUBLIC CONSTANTS
// --------------------------------------------------

#define ACC_UPDATE_RATE 5

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

int ACC_get_X();
int ACC_get_Y();
int ACC_get_Z();

void ACC_init(Timer* t);
void ACC_commands();

#endif	/* ACCELEROMETER_H */

