extern float PosR;                          //Define external variaables
extern float currentPosR;                           //Declare external variables for use in this part of the script
extern boolean AbsolutePos;
const float RhomingSpeedInDegPerSec = 8.0; 
const float RmaxHomingDistanceInSteps = 41000;   // The axis is max 300 mm long so homing for a longer distance does not make sense
const int directionTowardHomeR = 1;        // Direction to move toward limit switch: 1 goes positive direction, -1 backward
extern float RstepsDeg;                                        //Define the steps per Deg
extern int RspeedinDegs;                                     //Define the speed in Deg/s
extern const int LIMIT_SWITCH_R_PIN;
boolean homeR = false;
extern float HomePosition;


void Home() {  
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);                // Enable the steppers
  AbsolutePos = true;                               //Set the absolute positioning to true to be able to go to the home position accurately (NOTE THAT IF ON RELATIVE MODE HOMING WILL OVERRIDE TO ABSOLUTE MODE)
  PosR = HomePosition;                                         //Set the position to the homing position and home the steppers
  float RStepsPerSecond  = RstepsDeg * RspeedinDegs;
  Serial.println("Homing R");
  homeR = stepperR.moveToHomeInSteps(directionTowardHomeR, RStepsPerSecond, RmaxHomingDistanceInSteps, LIMIT_SWITCH_R_PIN);

  if (homeR){
  Serial.println("Homed");  
  currentPosR = -100;                                   //Set the position to the homing position and home the steppers
  }
  else{
  Serial.println("Failed");
  }
}
