/****************************************************
 * Serial Command Parser
 * Module: CMD
 * Hayk Martirosyan
 ****************************************************/

#ifndef COMMAND_PARSER_H
#define	COMMAND_PARSER_H

#include "Arduino.h"
#include "Timer.h"
#include "constants.h"
#include "bluetooth.h"

// --------------------------------------------------
// PUBLIC CONSTANTS
// --------------------------------------------------

#define CMD_DELIMITER ' '
#define CMD_UPDATE_RATE 500

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void CMD_check_command(String pCommand, void (*callback)(void));
void CMD_check_command(String pCommand, void (*callback)(int));
void CMD_test();
void CMD_command_received(String command);
void CMD_command_received(String command, int arg);

void CMD_init(Timer* t);
void CMD_commands();
#endif	/* COMMAND_PARSER_H */

