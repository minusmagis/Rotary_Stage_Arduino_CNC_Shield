extern float PosR;                          //Define external variaables
extern float currentPosR;                           //Declare external variables for use in this part of the script
extern boolean AbsolutePos;
const float RhomingSpeedInDegPerSec = 8.0; 
const float RmaxHomingDistanceInDeg = 200;   // The axis is max 300 mm long so homing for a longer distance does not make sense
const int directionTowardHomeR = -1;        // Direction to move toward limit switch: 1 goes positive direction, -1 backward
extern const int LIMIT_SWITCH_R_PIN;
boolean homeR = false;

void Home() {  
  AbsolutePos = true;                               //Set the absolute positioning to true to be able to go to the home position accurately (NOTE THAT IF ON RELATIVE MODE HOMING WILL OVERRIDE TO ABSOLUTE MODE)
  PosR = 0;                                         //Set the position to the homing position and home the steppers
  
  Serial.println("Homing Y");
  homeR = stepperR.moveToHomeInMillimeters(directionTowardHomeR, RhomingSpeedInDegPerSec, RmaxHomingDistanceInDeg, LIMIT_SWITCH_R_PIN);

  if (homeR){
  Serial.println("Homed");  
  currentPosR = 0;                                   //Set the position to the homing position and home the steppers
  }
  else{
  Serial.println("Failed");
  }
}
