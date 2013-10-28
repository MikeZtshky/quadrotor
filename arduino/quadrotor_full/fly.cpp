/****************************************************
* Fly Module
* Module:FLY
* Hayk Martirosyan
****************************************************/

#include "fly.h"

// --------------------------------------------------
// PRIVATE CONSTANTS
// --------------------------------------------------

#define BASE_THROTTLE 0.1

#define FULL_TURN_THROTTLE_OFFSET 0.4

// --------------------------------------------------
// PRIVATE VARIABLES
// --------------------------------------------------

float P_GAIN = 20.0;
float D_GAIN = 20.0;

float base_throttle = BASE_THROTTLE;

boolean stopped = true;

float NE_offset;
float SE_offset;
float SW_offset;
float NW_offset;

float NE_throttle;
float SE_throttle;
float SW_throttle;
float NW_throttle;

float NE_p_offset;
float SE_p_offset;
float SW_p_offset;
float NW_p_offset;

float NE_d_offset;
float SE_d_offset;
float SW_d_offset;
float NW_d_offset;

float N_turn_offset = 0;
float E_turn_offset = 0;

// --------------------------------------------------
// PRIVATE METHODS
// --------------------------------------------------

void FLY_print() {
  if(stopped)
    return;
  
  Serial.print("THROTTLES | ");
  Serial.print("NE: ");
  Serial.print(NE_throttle);
  Serial.print(", SE: ");
  Serial.print(SE_throttle);
  Serial.print(", SW: ");
  Serial.print(SW_throttle);
  Serial.print(", NW: ");
  Serial.println(NW_throttle);
}

void FLY_print_gains() {
  if(stopped)
    return;
  
  Serial.print("NW | ");
  Serial.print("p_offset: ");
  Serial.print(NW_p_offset);
  Serial.print(", d_offset: ");
  Serial.print(NW_d_offset);
  Serial.print(", sum: ");
  Serial.print(NW_offset);
  Serial.print(", throttle: ");
  Serial.println(NW_throttle);
}

void FLY_update() {
  
  if (stopped)
    return;
  
  NE_p_offset = -ACC_get_Z()* P_GAIN/1000.;
  SE_p_offset = +ACC_get_Y()* P_GAIN/1000.;
  SW_p_offset = +ACC_get_Z()* P_GAIN/1000.;
  NW_p_offset = -ACC_get_Y()* P_GAIN/1000.;
  
  NE_d_offset = - ACC_get_dZ()*D_GAIN/1000.;
  SE_d_offset = + ACC_get_dY()*D_GAIN/1000.;
  SW_d_offset = + ACC_get_dZ()*D_GAIN/1000.;
  NW_d_offset = - ACC_get_dY()*D_GAIN/1000.;
  
  NE_offset = NE_p_offset + NE_d_offset;
  SE_offset = SE_p_offset + SE_d_offset;
  SW_offset = SW_p_offset + SW_d_offset;
  NW_offset = NW_p_offset + NW_d_offset;
  
  NE_throttle = base_throttle + (1 - base_throttle) * NE_offset;
  SE_throttle = base_throttle + (1 - base_throttle) * SE_offset;
  SW_throttle = base_throttle + (1 - base_throttle) * SW_offset;
  NW_throttle = base_throttle + (1 - base_throttle) * NW_offset;
  
  NE_throttle = NE_throttle + N_turn_offset + E_turn_offset;
  SE_throttle = SE_throttle - N_turn_offset + E_turn_offset;
  SW_throttle = SW_throttle - N_turn_offset - E_turn_offset;
  NW_throttle = NW_throttle + N_turn_offset - E_turn_offset;
  
  NE_throttle = constrain(NE_throttle, 0.0, 1.0);
  SE_throttle = constrain(SE_throttle, 0.0, 1.0);
  SW_throttle = constrain(SW_throttle, 0.0, 1.0);
  NW_throttle = constrain(NW_throttle, 0.0, 1.0);
  
  //NE_throttle = sqrt(NE_throttle);
  //SE_throttle = sqrt(SE_throttle);
  //SW_throttle = sqrt(SW_throttle);
  //NW_throttle = sqrt(NW_throttle);
  
  MDR_set_desired_speed(NE_MOTOR, NE_throttle);
  MDR_set_desired_speed(SE_MOTOR, SE_throttle);
  MDR_set_desired_speed(SW_MOTOR, SW_throttle);
  MDR_set_desired_speed(NW_MOTOR, NW_throttle);
}

void FLY_fly() {
 stopped = false; 
}

void FLY_stop() {
  stopped = true;
  
  N_turn_offset = 0;
  E_turn_offset = 0;
  
  NE_throttle = 0;
  SE_throttle = 0;
  SW_throttle = 0;
  NW_throttle = 0;
  
  NE_offset = 0;
  SE_offset = 0;
  SW_offset = 0;
  NW_offset = 0;
}

// zero to 255
void FLY_set_base_throttle(int throttle) {
  if((throttle > 255) || (throttle < 0)) {
    Serial.println("INVALID THROTTLE, IGNORING!");
    return;
  }
 
  base_throttle = (float)throttle/255.0;
}

// zero to 255
void FLY_set_N_turn_offset(int offset) {
  if((offset > 255) || (offset < -255)) {
    Serial.println("INVALID THROTTLE, IGNORING!");
    return;
  }
   N_turn_offset = (float)offset/255.0 * FULL_TURN_THROTTLE_OFFSET;
}

// zero to 255
void FLY_set_E_turn_offset(int offset) {
  if((offset > 255) || (offset < -255)) {
    Serial.println("INVALID THROTTLE, IGNORING!");
    return;
  }
   E_turn_offset = (float)offset/255.0 * FULL_TURN_THROTTLE_OFFSET;
}

void FLY_set_D_gain(int gain) {
  D_GAIN = (float)gain;
}

void FLY_set_P_gain(int gain) {
  P_GAIN = (float)gain;
}

void FLY_init(Timer* t) {
  
  // Fast motor update loop
  t->every(FLY_UPDATE_RATE, FLY_update);
  t->every(FLY_PRINT_RATE, FLY_print_gains);
  
}

void FLY_commands() {  
  
  // Commands
  CMD_check_command(String("STOP"), FLY_stop);
  CMD_check_command(String("FLY"), FLY_fly);
  CMD_check_command(String("STRENGTH"), FLY_set_base_throttle);
  CMD_check_command(String("N_TURN"), FLY_set_N_turn_offset);
  CMD_check_command(String("E_TURN"), FLY_set_E_turn_offset);
  CMD_check_command(String("D_GAIN"), FLY_set_D_gain);
  CMD_check_command(String("P_GAIN"), FLY_set_P_gain);
}

