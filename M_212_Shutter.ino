//Connection pins on the arduino are 11 10 9 8  for the shutter that has an elbow on the connector and 7 6 5 4 for the other one, if shutters do not behave correctly turn around the connections

extern const int SHUTTER_PIN_1;
extern const int SHUTTER_PIN_2;
extern const int SHUTTER_PIN_3;
extern const int SHUTTER_PIN_4;

void Wait() {
  bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
  for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
    if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
      switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction
        case 'S':                                         //If the case is X it means we want to change the X position so we will scan the following numbers to know to which position we have to move
          {
            openShutter();
            delay(SubCommandExtractor(i).toInt() * 1000);
            closeShutter();
            //        Serial.println("S checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'P':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            openShutter();
            delay(SubCommandExtractor(i).toInt());
            closeShutter();
            //        Serial.println("P checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'D':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            Demo();
            //        Serial.println("D checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case ';':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        default:
          {
            UnknownCommand();                                 //In the case of anything else, send: Unknown Command
            endMarker = true;                                 //And break the for loop that was looking for other attributes of the G command
          }
          break;
      }
    }
    else if (endMarker == true) {
      break;
    }
  }
}


// Low level functions that control the movement of the shutter stepper

int stepDelay = 10; // Delay between steps in milliseconds; adjust to minimum level for time sensitive applications

void Demo() {
  for (int i = 0; i < 13; i++) {
    openShutter();
    delay(10);
    closeShutter();
    delay(10);
  }
}

void step1() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  delay(stepDelay);

}
void step2() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, HIGH);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  delay(stepDelay);
}
void step3() {
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, HIGH);
  delay(stepDelay);
}
void step4() {
  digitalWrite(inA1, HIGH);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, HIGH);
  digitalWrite(inB2, LOW);
  delay(stepDelay);
}
void stopMotor() {
  digitalWrite(inA1, LOW);
  digitalWrite(inA2, LOW);
  digitalWrite(inB1, LOW);
  digitalWrite(inB2, LOW);
}

void closeShutter() {
  step1();
  step3();
  step2();
}

void openShutter() {
  step3();
  step4();
  step1();
  step2();
}
