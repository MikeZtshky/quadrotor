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

#define ACC_UPDATE_RATE 1
#define ACC_PRINT_RATE 20000

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

int ACC_get_X();
int ACC_get_Y();
int ACC_get_Z();
long ACC_get_dY();
long ACC_get_dZ();

void ACC_print();
void ACC_print_raw();

void ACC_init(Timer* t);
void ACC_commands();
void ACC_update();

#endif	/* ACCELEROMETER_H */

