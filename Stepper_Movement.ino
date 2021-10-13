extern const int STEPPERS_ENABLE_PIN;
extern const int MOTOR_R_STEP_PIN;
extern const int MOTOR_R_DIR_PIN;
extern const int LIMIT_SWITCH_R_PIN;

float RstepsDeg = 80;                                        //Define the steps per Deg
int RspeedinDegs = 10;                                     //Define the speed in Deg/s
int RDegss = 1;                                            //Define the acceleration in Deg/s^2

int Rmotor_dir = -1;                               // Invert the direction if the motor is plugged in reverse (1 is normau -1 is reversed)

float RStepsPerSecond = RstepsDeg * RspeedinDegs;                                       //in steps per second (has to be calibrated)
float RStepsPerSecondPerSecond = RstepsDeg * RDegss;                              //in steps per second per second (has to be calibrated)

void MoveSteppers(float Rmove) {
  float stepsR = Rmove * Rstepsmm;
  long Final_R_Steps = round(stepsR) * Rmotor_dir;                    // We need to round to convert to int to avoid truncation problems  
//  Serial.print("Steps R= ");
//  Serial.println(stepsR);
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
