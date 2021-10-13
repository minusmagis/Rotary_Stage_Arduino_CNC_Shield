#include <SpeedyStepper.h>


// First we set all the constants to the connection pins
const int STEPPERS_ENABLE_PIN = 8;
const int MOTOR_R_STEP_PIN = 2;
const int MOTOR_R_DIR_PIN = 7;
const int LIMIT_SWITCH_R_PIN = 9;

const int SHUTTER_PIN_1 = ;
const int SHUTTER_PIN_2 = ;
const int SHUTTER_PIN_3 = ;
const int SHUTTER_PIN_4 = ;


extern float RstepsDeg;
extern int RDegss;


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

  digitalWrite(STEPPERS_ENABLE_PIN, LOW);                // Enable the steppers

  Serial.begin(9600);                                    // Begin Serial communication
  StartCode();                                           // Send the startcode
}

void loop() {
  GcodeCommandReceive();
  GcodeToInstructions();
}
