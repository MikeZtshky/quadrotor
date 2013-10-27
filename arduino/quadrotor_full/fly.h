/****************************************************
* FLY Module
* Module:FLY
* Hayk Martirosyan
****************************************************/

#ifndef FLY_H
#define	FLY_H

#include "Arduino.h"
#include "Timer.h"

#include "constants.h"
#include "command_parser.h"

// --------------------------------------------------
// PUBLIC CONSTANTS
// --------------------------------------------------

#define FLY_UPDATE_RATE 5

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void FLY_init(Timer* t);
void FLY_commands();

#endif	/* FLY_H */

