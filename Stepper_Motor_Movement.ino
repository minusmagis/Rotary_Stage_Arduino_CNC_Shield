extern boolean AbsolutePos;
extern float currentPosR;                           //Declare external variables for use in this part of the script
extern float PosR;
extern int Feedrate;
extern boolean AllowedPosition;
extern int RaxisRangeMaxDeg;                                  //Declare the min range of the r axis (in deg)
extern int RaxisRangeMinDeg;                                  //Declare the max range of the r axis (in deg)


void SetSteppersMovement() {
  //  Serial.println("Move Steppers Checked");           //For Development purposes
  float Rmove = 0;                                       //This variable stores the direction vector towards which we want the R stage to move

  if (AbsolutePos == true)                               //If the R stage is in absolute position movement calculate the coordinates for the moving vector
  {
    Rmove = PosR - currentPosR;                         //Scan the PosR and calculate the distance between the desired position and the current position
    currentPosR = PosR;
    //    Serial.print("Movement in the r position: "); //For development purposes
    //    Serial.print(RMove);
    //    Serial.println("Absolute Check");
  }

  else {                                       //If the arm is in relative position movement use the coordinates as the moving vector
    {
      Rmove = PosR;                                //Scan the PosR and set it to be the direction vector since the R carriage is in relative position movement
      //    Serial.print("Movement in the r position: "); //For development purposes
      //    Serial.print(RMove);
      //    Serial.println("Relative Check");
    }
    currentPosR = currentPosR + PosR;                             // The new position will be the one we were in plus the one we have added with the relative movement
  }
  MoveSteppers(Rmove);

}

boolean PositionAllowed() {                                                                                 //Check if the position to which the command tells the carriage to move is within the carriage range, and if so return true, otherwise return false
  if (AbsolutePos == true) {
    if ( RaxisRangeMinDeg <= PosR && PosR <= RaxisRangeMaxDeg ) {                                           //If the desired position is whithin this range the movement is allowed
//      Serial.println("Whithin range Abs");                                                                //For development purposes
      return true;

    }
    else {
//      Serial.println("Out of range Abs");                                                                 //For development purposes
      return false;

    }
  }
  else {
    float Rfinal = 0;                                                   //Create a variable that will hold the final position to prevent moving beyond the set boundaries of the arm in relative mode
    Rfinal = PosR + currentPosR;                                        //Set the final position to the sum of the current position plus the amount we want to move
    if (RaxisRangeMinDeg <= Rfinal && Rfinal <= RaxisRangeMaxDeg) {     //If the final calculated position is whithin this range the movement is allowed
//      Serial.println("Whithin range rel");                            //For development purposes
      return true;
    }
    else {
//      Serial.println("Out of range rel");                             //For development purposes
      return false;
    }
  }
}
