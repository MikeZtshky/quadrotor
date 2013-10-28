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

// Number of past values averaged for accelerometer readings
#define SMOOTHING 50

#define D_COUNT 40

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

static long x_accel = 0;
static long y_accel = 0;
static long z_accel = 0;

static long x_accel_d = 0;
static long y_accel_d = 0;
static long z_accel_d = 0;

static int hist_x[SMOOTHING];
static int hist_y[SMOOTHING];
static int hist_z[SMOOTHING];

static int base_x = 0;
static int base_y = 0;
static int base_z = 0;

Timer* timer;

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

int ACC_get_X() {
  return x_accel - base_x;
}

int ACC_get_Y() {
  return y_accel - base_y;
}

int ACC_get_Z() {
  return z_accel - base_z;
}

void ACC_print() {
  Serial.print("ACC smoothed | ");
  Serial.print(", Y: ");
  Serial.print(ACC_get_Y());
  Serial.print(", Z: ");
  Serial.print(ACC_get_Z());
  Serial.print(", dY: ");
  Serial.print(ACC_get_dY());
  Serial.print(", dZ: ");
  Serial.print(ACC_get_dZ());
  Serial.println("");
}

void ACC_print_raw() {
  Serial.print("ACC raw | ");
  Serial.print(", Y: ");
  Serial.print(analogRead(Y_ACCEL_PIN));
  Serial.print(", Z: ");
  Serial.print(analogRead(Z_ACCEL_PIN));
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

long ACC_get_dY() {
  return y_accel_d;
}

long ACC_get_dZ() {
  return z_accel_d;
}

void ACC_update() {
  
  // Shift the values back
  for(int i = SMOOTHING - 1; i > 0; i--) {
    //hist_x[i] = hist_x[i-1];
    hist_y[i] = hist_y[i-1];
    hist_z[i] = hist_z[i-1];
  }
  
  // Fill in new values
  //hist_x[0] = analogRead(X_ACCEL_PIN);
  hist_y[0] = analogRead(Y_ACCEL_PIN);
  hist_z[0] = analogRead(Z_ACCEL_PIN);
  
  // Create averages
  x_accel = 0;
  y_accel = 0;
  z_accel = 0;
  for(int i = 0; i < SMOOTHING; i++) {
    //x_accel += hist_x[i];
    y_accel += hist_y[i];
    z_accel += hist_z[i];
    if(i == (D_COUNT-1)) {
      y_accel_d = y_accel/(D_COUNT);
      z_accel_d = z_accel/(D_COUNT);
    }
  }
  //x_accel = x_accel/SMOOTHING;
  y_accel = y_accel/SMOOTHING;
  z_accel = z_accel/SMOOTHING;
  
  y_accel_d = y_accel - y_accel_d;
  z_accel_d = z_accel - z_accel_d;
}

void get_base_value_blocking() {
  
  for(int i = 0; i < SMOOTHING; i++) {
    ACC_update();
    delay(ACC_UPDATE_RATE);
  }
  base_x = x_accel;
  base_y = y_accel;
  base_z = z_accel;
  Serial.print("Base values: " + String(base_x) + ", " + String(base_y) + ", " + String(base_z));
}

void ACC_init(Timer* t) {
  
  //t->every(ACC_UPDATE_RATE, ACC_update);
  
  t->every(ACC_PRINT_RATE, ACC_print);
  
  timer = t;
  
  //analogReference(INTERNAL);
  get_base_value_blocking();
}

void ACC_commands() {  
  
  // Commands
  CMD_check_command(String("ACC_PRINT"), ACC_print);
  
  CMD_check_command(String("ACC_SEND_X"), ACC_send_X);
  CMD_check_command(String("ACC_SEND_Y"), ACC_send_Y);
  CMD_check_command(String("ACC_SEND_Z"), ACC_send_Z);
}

