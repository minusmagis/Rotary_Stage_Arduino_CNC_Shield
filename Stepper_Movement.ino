extern const int STEPPERS_ENABLE_PIN;
extern const int MOTOR_R_STEP_PIN;
extern const int MOTOR_R_DIR_PIN;
extern const int LIMIT_SWITCH_R_PIN;

extern float RstepsDeg;                                        //Define the steps per Deg
extern int RspeedinDegs;                                     //Define the speed in Deg/s
extern int RDegss;                                            //Define the acceleration in Deg/s^2

extern int Feedrate;

int Rmotor_dir = -1;                               // Invert the direction if the motor is plugged in reverse (1 is normau -1 is reversed)

float RStepsPerSecondPerSecond = RstepsDeg * RDegss;                              //in steps per second per second (has to be calibrated)

void MoveSteppers(float Rmove) {
  digitalWrite(STEPPERS_ENABLE_PIN, LOW);                // Enable the steppers
  float stepsR = Rmove * RstepsDeg;
  long Final_R_Steps = round(stepsR) * Rmotor_dir;                    // We need to round to convert to int to avoid truncation problems  
//  Serial.println("Final Steps: ");
//  Serial.println(Final_R_Steps);
//  Serial.print("Steps R= ");
//  Serial.println(stepsR);
  float RStepsPerSecond  = RstepsDeg * RspeedinDegs * Feedrate / 100;
  stepperR.setSpeedInStepsPerSecond(RStepsPerSecond);
  stepperR.setupRelativeMoveInSteps(Final_R_Steps);
  //
  // now execute the moves, looping until both motors have finished
  //
  while (!stepperR.motionComplete())
  {
    stepperR.processMovement();
  }
  Serial.println("Moved");
 
}

void DisableSteppers(){
    digitalWrite(STEPPERS_ENABLE_PIN, HIGH);                // Disable the steppers
    Serial.println("Steppers Disabled");
}
