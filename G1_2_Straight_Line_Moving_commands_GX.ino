float PosR = 0;
int Feedrate = 100;
float currentPosR = 0;                   //The values at which the servos naturally start
extern boolean AbsolutePos;

float Round_To_decimals (float To_Round,int decimals = 1)       // This function takes any float and rounds it to a certain number of decimals
{
  float Rounded = To_Round;
   decimals = constrain(decimals, 0, 9);
  for (int i = decimals; i>0;i--){
    Rounded *= 10;
  }
  Rounded = round(Rounded);
    for (int i = decimals; i>0;i--){
    Rounded /= 10;
  }
  return Rounded;
}


void MovingCommand() {
  bool endMarker = false;                                 //Define a variable to break the for loop from inside a case structure
  if (AbsolutePos == false) { 
      PosR = 0;                                           //Reinitialize the value of desired position before reading the new desired value
  }
  else{                         
      PosR = currentPosR;                                 //Reinitialize the value of desired position before reading the new desired value
  }
  for (int i = 0; i < 64; i++) {                          //Read the entire command in search for the attributes of the movement such as position velocity or if the laser should be on or off
    if (Command[i] == ' ' && endMarker == false) {        //Detect the next space that will indicate that a new attribute is expected (G1 X23.34)
      switch (Command[i + 1]) {                           //The switch will read the letter immediately after the space which will indicate the attribute of this movement instruction
        case 'R':                                         //If the case is X it means we want to change the X position so we will scan the following numbers to know to which position we have to move
          {
            PosR = Round_To_decimals(SubCommandExtractor(i).toFloat());
                    Serial.println("R checked");                    //For development purposes
          }
          break;                                          //Break the loop to continue looking for other attributes

        case 'F':                                         //If the case is Y it means we want to change the Y position so we will scan the following numbers to know to which position we have to move
          {
            Feedrate = round(SubCommandExtractor(i).toFloat());
                    Serial.println("F checked");                //For development purposes
                    Serial.println(Feedrate);                //For development purposes
          }
          break;

        case ';':                                         //If the case is ;
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        case '\n':                                         //If the case is \n
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        case '\0':                                         //If the case is \0
          endMarker = true;                               //Set the endmarker flag to true to stop the loop
          break;

        case ' ':                                         //If the case is ' '
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
    if (PositionAllowed() == true){
      SetSteppersMovement();
    }
    else{
      Serial.println("Coordinate out of range!");
    }

}
