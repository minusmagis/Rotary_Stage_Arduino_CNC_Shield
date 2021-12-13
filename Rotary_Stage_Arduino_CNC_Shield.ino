#include <SpeedyStepper.h>

/*
   Command List:

   G0 or G1 +args -> rotation. specifier R and amount to move F for the feedrate (F100 is the default and values can go higher or lower). Syntax: G1 R100 F50 (Translation: Move to 100 deg position at half the normal speed)
   G28 -> Home Motor
   M114 -> Responds with the current position
   M212 +args -> Open and close the shutter for a given ammount of time specified by using S or P. S for Seconds P for milliseconds. Optional argument D adds a delay before the shutter. Syntax: M212 P500 D200 (Translation: Open the shutter for 500 ms after 200ms of receiving the signal)
   M213 -> Open shutter
   M214 -> Close shutter
   M18 -> Disable Steppers
   M220 -> Take Photograph (multiple pulses) Start QE measurement. Wait for a specified ammount of time (D) and then send (P) trigger events to the laser with the specified (R) repetition rate. Syntax: M220 P5 D50 R10 (Translation: Photograph with 5 pulses with a 50ms initial delay and a 10hz repetition rate)

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

const int TRIGGER_PIN = 10;
const int LASER_EXT_TRIGGER_PIN = 4;
const int LASERTRIGGERGND = 3;

const int LaserPeriod = 10; // In ms

unsigned long StartMillis;  //some global variables available anywhere in the program

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

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(LASER_EXT_TRIGGER_PIN, OUTPUT);
  pinMode(LASERTRIGGERGND, OUTPUT);
  digitalWrite(LASERTRIGGERGND, LOW);

  stepperR.connectToPins(MOTOR_R_STEP_PIN, MOTOR_R_DIR_PIN);        //Initialize the motors
  stepperR.setStepsPerMillimeter(RstepsDeg);
  stepperR.setAccelerationInMillimetersPerSecondPerSecond(RDegss);

  digitalWrite(STEPPERS_ENABLE_PIN, HIGH);               // Disable the steppers

  Serial.begin(19200);                                    // Begin Serial communication
  StartCode();                                           // Send the startcode
  closeShutter();                                        // Start With the shutter closed
}

void loop() {
  GcodeCommandReceive();
  GcodeToInstructions();
}
