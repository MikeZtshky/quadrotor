/****************************************************
* Motor Driver
* Module: MDR
* Hayk Martirosyan
****************************************************/

#include "motor_driver.h"

// --------------------------------------------------
// PRIVATE CONSTANTS
// --------------------------------------------------

#define MDR_ZERO 1000
#define MDR_FULL 2000

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

// One servo object per motor stack
static Servo motors[MDR_NUM_MOTORS];

static int motor_pins[] = {11, 9, 6, 3};

static double desired_speed[MDR_NUM_MOTORS];

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

/**
* Ramps a motor toward the desired speed.
*/
static void MDR_drive(int motor) {
    
    double current_speed = MDR_get_speed(motor);
    
    if (current_speed < desired_speed[motor])
      current_speed += .01;
    else if (current_speed > desired_speed[motor])
      current_speed -= .01;
    
    MDR_set_speed(motor, current_speed);
}

static void MDR_update() {
  
  for(int i = 0; i < MDR_NUM_MOTORS; i++) {
    MDR_drive(i);
  }
}

// --------------------------------------------------
// PUBLIC METHODS
// --------------------------------------------------

/**
* Sets the motor speed using a number between 0 and 1.
*/
void MDR_set_speed(int motor, double throttle) {
  
  int ms = throttle * (MDR_FULL - MDR_ZERO) + MDR_ZERO;
  motors[motor].writeMicroseconds(ms);
}

/**
* Gets the motor speed as a number between 0 and 1.
*/
double MDR_get_speed(int motor) {
  
  int ms = motors[motor].readMicroseconds();
  
  return (double)(ms - MDR_ZERO)/(MDR_FULL - MDR_ZERO);
}

/**
* Sets the desired motor speed using a number between 0 and 1.
*/
void MDR_set_desired_speed(int motor, double throttle) {
  desired_speed[motor] = throttle;
}

/**
* Gets the desired motor speed as a number between 0 and 1.
*/
double MDR_get_desired_speed(int motor) {
  return desired_speed[motor];
}

void MDR_print_speed(int motor) {
  
  Serial.print("Motor ");
  Serial.print(motor);
  Serial.print(" speed - ");
  Serial.print("Actual: ");
  Serial.print(MDR_get_speed(motor));
  Serial.print(", Desired: ");
  Serial.println(desired_speed[motor]);
}

void MDR_print_speeds() {
  for(int i = 0; i < MDR_NUM_MOTORS; i++)
    MDR_print_speed(i);
}

void MDR_stop(int motor) {
  MDR_set_speed(motor, 0);
  MDR_set_desired_speed(motor, 0);
}

void MDR_stop_all() {
  for(int i = 0; i < MDR_NUM_MOTORS; i++)
     MDR_stop(i);
}

void MDR_set_desired_speed_all(double throttle) {
  for(int i = 0; i < MDR_NUM_MOTORS; i++)
    MDR_set_desired_speed(i, throttle);
}

void MDR_0() {
  MDR_set_desired_speed_all(0.0);
}

void MDR_1() {
  MDR_set_desired_speed_all(0.1);
}

void MDR_2() {
  MDR_set_desired_speed_all(0.2);
}

void MDR_3() {
  MDR_set_desired_speed_all(0.3);
}

void MDR_4() {
  MDR_set_desired_speed_all(0.4);
}

void MDR_5() {
  MDR_set_desired_speed_all(0.5);
}

void MDR_6() {
  MDR_set_desired_speed_all(0.6);
}

void MDR_7() {
  MDR_set_desired_speed_all(0.7);
}

void MDR_8() {
  MDR_set_desired_speed_all(0.8);
}

void MDR_9() {
  MDR_set_desired_speed_all(0.9);
}

void MDR_init(Timer* t) {
  
  for(int i = 0; i < MDR_NUM_MOTORS; i++) {
    motors[i] = Servo();
    motors[i].attach(motor_pins[i]);
    MDR_stop(i);
  }
  
  // Fast motor update loop
  t->every(MDR_UPDATE_RATE, MDR_update);
  
  // Position printing loop
  t->every(MDR_PRINT_LOOP_RATE, MDR_print_speeds);
}

void MDR_commands() {
  
  // Commands
  CMD_check_command(String("MDR_STOP"), MDR_stop_all);
  CMD_check_command(String("MDR_0"), MDR_0);
  CMD_check_command(String("MDR_1"), MDR_1);
  CMD_check_command(String("MDR_2"), MDR_2);
  CMD_check_command(String("MDR_3"), MDR_3);
  CMD_check_command(String("MDR_4"), MDR_4);
  CMD_check_command(String("MDR_5"), MDR_5);
  CMD_check_command(String("MDR_6"), MDR_6);
  CMD_check_command(String("MDR_7"), MDR_7);
  CMD_check_command(String("MDR_8"), MDR_8);
  CMD_check_command(String("MDR_9"), MDR_9);
}

