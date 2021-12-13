extern const int LASER_EXT_TRIGGER_PIN;

//Connection pins on the arduino are 11 10 9 8  for the shutter that has an elbow on the connector and 7 6 5 4 for the other one, if shutters do not behave correctly turn around the connections

extern const int SHUTTER_PIN_1;
extern const int SHUTTER_PIN_2;
extern const int SHUTTER_PIN_3;
extern const int SHUTTER_PIN_4;

extern const int LaserPeriod;

int TriggerDelay = 5;

int PulseNumber = 0;
int InitialDelayTime = 50;
int RepetitionRate = 0;

void Photograph_Subroutine(int PulseNumber = 0, int InitialDelayTime = 50, int RepetitionRate = 0)
{
  openShutter();
  int RepetitionDelay = (1000 / RepetitionRate) - 2*TriggerDelay;
  Trigger();                                         // QE Pro initiates integration (time) of the measurement
  delay(InitialDelayTime);

  for (int i = 0; i <= PulseNumber; i++) {
    Trigger_Laser();
    delay(RepetitionDelay);
  }
  Serial.println("Photograph done");                    //For development purposes
  closeShutter();
}

void Photograph() {
  bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
  bool ValidCommand = true;
  for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
    if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
      switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction
        case 'P':                                         //If the case is X it means we want to change the X position so we will scan the following numbers to know to which position we have to move
          {
            PulseNumber = SubCommandExtractor(i).toInt();
//                                Serial.println("P checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'D':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            InitialDelayTime = SubCommandExtractor(i).toInt();
//                                Serial.println("D checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'R':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            RepetitionRate = SubCommandExtractor(i).toInt();
//                    Serial.println("R checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case ';':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        default:
          {
            UnknownCommand();                                 //In the case of anything else, send: Unknown Command
            ValidCommand = false;
            endMarker = true;                                 //And break the for loop that was looking for other attributes of the G command
          }
          break;
      }
    }
    else if (endMarker == true) {
      break;
    }
  }
  Photograph_Subroutine(PulseNumber, InitialDelayTime, RepetitionRate);
}


void Trigger_Laser() {                          // Set the trigger pin to high for 1 ms
  digitalWrite(LASER_EXT_TRIGGER_PIN, HIGH);
  delay(TriggerDelay);
  digitalWrite(LASER_EXT_TRIGGER_PIN, LOW);
  delay(TriggerDelay);
//  Serial.println("Trigger Event");
}
