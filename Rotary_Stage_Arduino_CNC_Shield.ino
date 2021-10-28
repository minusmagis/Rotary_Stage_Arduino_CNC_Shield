#include <SpeedyStepper.h>

/*
 * Command List:
 * 
 * G0 or G1 +args -> rotation. specifier R and amount to move F for the feedrate (F100 is the default and values can go higher or lower). Syntax: G1 R100 F50 (Translation: Move to 100 deg position at half the normal speed)
 * G28 -> Home Motor
 * M114 -> Responds with the current position
 * M212 +args -> Open and close the shutter for a given ammount of time specified by using S or P. S for Seconds P for milliseconds. Syntax: M212 P500 (Translation: Open the shutter for 500 ms) 
 * M213 -> Open shutter
 * M214 -> Close shutter
 * M18 -> Disable Steppers
 * 
 * 
 */
 
// First we set all the constants to the connection pins
const int STEPPERS_ENABLE_PIN = 8;
const int MOTOR_R_STEP_PIN = 2;
const int MOTOR_R_DIR_PIN = 5;
const int LIMIT_SWITCH_R_PIN = 11;

const int SHUTTER_PIN_1 = 9;
const int SHUTTER_PIN_2 = 12;
const int SHUTTER_PIN_3 = 13;
const int SHUTTER_PIN_4 = 17;


float RstepsDeg = 189;                                        //Define the steps per Deg
int RspeedinDegs = 4;                                     //Define the speed in Deg/s
int RDegss = 4;                                            //Define the acceleration in Deg/s^2

// 1 revolution big * 20/420 gear ratio * 800 steps / revolution small

int RaxisRangeMaxDeg = 120;                                  //Declare the min range of the r axis (in deg)
int RaxisRangeMinDeg = -90;                                  //Declare the max range of the r axis (in deg)

float HomePosition = -100;                                  // Declare the position of the motor when homed


SpeedyStepper stepperR;


void setup() {
  pinMode(STEPPERS_ENABLE_PIN, OUTPUT);                  // Set the enable pin as an output
  pinMode(LIMIT_SWITCH_R_PIN, INPUT_PULLUP);

  pinMode(SHUTTER_PIN_1, OUTPUT);
  pinMode(SHUTTER_PIN_2, OUTPUT);
  pinMode(SHUTTER_PIN_3, OUTPUT);
  pinMode(SHUTTER_PIN_4, OUTPUT);

  stepperR.connectToPins(MOTOR_R_STEP_PIN, MOTOR_R_DIR_PIN);        //Initialize the motors
  stepperR.setStepsPerMillimeter(RstepsDeg);
  stepperR.setAccelerationInMillimetersPerSecondPerSecond(RDegss);

  digitalWrite(STEPPERS_ENABLE_PIN, HIGH);               // Disable the steppers

  Serial.begin(9600);                                    // Begin Serial communication
  StartCode();                                           // Send the startcode
  closeShutter();                                        // Start With the shutter closed
}

void loop() {
  GcodeCommandReceive();
  GcodeToInstructions();
}
