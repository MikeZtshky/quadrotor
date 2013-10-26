/****************************************************
* Motor Driver
* Module: MDR
* Hayk Martirosyan
****************************************************/

#ifndef MOTOR_DRIVER_H
#define	MOTOR_DRIVER_H

#include "Arduino.h"
#include "Timer.h"
#include "Servo.h"

#include "constants.h"
#include "command_parser.h"

// --------------------------------------------------
// PUBLIC CONSTANTS
// --------------------------------------------------

#define MDR_UPDATE_RATE 2
#define MDR_PRINT_LOOP_RATE 1000

#define MDR_NUM_MOTORS 4

// --------------------------------------------------
// PUBLIC VARIABLES
// --------------------------------------------------

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

void MDR_set_speed(int motor, double throttle);
double MDR_get_speed(int motor);

void MDR_set_desired_speed(int motor, double throttle);
void MDR_set_desired_speed_all(double throttle);
double MDR_get_desired_speed(int motor);

void MDR_stop_all();

void MDR_print_speed(int motor);
void MDR_print_speeds();

void MDR_init(Timer* t);
void MDR_commands();

#endif	/* MOTOR_DRIVER_H */

