/****************************************************
* Accelerometer Module
* Module:ACC
* Hayk Martirosyan
****************************************************/

#include "accelerometer.h"

// --------------------------------------------------
// PRIVATE CONSTANTS
// --------------------------------------------------

#define X_ACCEL_PIN A0
#define Y_ACCEL_PIN A1
#define Z_ACCEL_PIN A2

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

static int x_accel;
static int y_accel;
static int z_accel;

static int avg_x;
static int avg_y;
static int avg_z;

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

int ACC_get_X() {
  return x_accel;
}

int ACC_get_Y() {
  return y_accel;
}

int ACC_get_Z() {
  return z_accel;
}

void ACC_print() {
  Serial.print("X: ");
  Serial.print(x_accel);
  Serial.print(", Y: ");
  Serial.print(y_accel);
  Serial.print(", Z: ");
  Serial.print(z_accel);
  Serial.println("");
}

void ACC_send_X() {
  BLU_send_command("ACC_X", ACC_get_X());
}

void ACC_send_Y() {
  BLU_send_command("ACC_Y", ACC_get_Y());
}

void ACC_send_Z() {
  BLU_send_command("ACC_Z", ACC_get_Z());
}

void ACC_update() {
  x_accel = analogRead(X_ACCEL_PIN);
  y_accel = analogRead(Y_ACCEL_PIN);
  z_accel = analogRead(Z_ACCEL_PIN);
  Serial.println(String(x_accel) + " " + String(y_accel) + " " + String(z_accel));
}

void ACC_init(Timer* t) {
  
  // Fast motor update loop
  t->every(ACC_UPDATE_RATE, ACC_update);
  //analogReference(EXTERNAL);
}

void ACC_commands() {  
  
  // Commands
  CMD_check_command(String("ACC_PRINT"), ACC_print);
  
  CMD_check_command(String("ACC_SEND_X"), ACC_send_X);
  CMD_check_command(String("ACC_SEND_Y"), ACC_send_Y);
  CMD_check_command(String("ACC_SEND_Z"), ACC_send_Z);
}

