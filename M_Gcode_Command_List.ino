void MGcode(){                                  //Function that runs in the event of a MXXX command More functionalities will be added with time as they are needed
  //Serial.println("M Checked");                //For development purposes
  switch(CommandNumberExtractor()){             //Read the command number after the M of the M command to know exactly which command it is
    case 21:
      Serial.println("echo:SD init fail");      //In case M21 (initialize SD) send an echo fail message stating that there was no SD
    break;

    case 114:
      GetCurrentPosition();                     //In case M114 Send the current position of the arm 
    break;
    
    case 115:
      FirmwareCapabilities();                   //In case M115 Send the firmware capabilities of this arm 
    break;

    case 212:
      Shutter_Snapshot();                   //In case M212 Open the shutter for a specific amount of time defined in the command
    break;

    case 213:
      openShutter();                        //In case M213 Open the shutter
    break;

    case 214:
      closeShutter();                         //In case M214 close the shutter
    break;

    case 215:                                 //In case M215 send the trigger signal
      Trigger();
    break;

    case 220:                                 //In case M220 send the trigger_Laser signal
      Photograph();
    break;

    case 18:
      DisableSteppers();                         //In case M18 disengage motor
    break;

    default:
    {
      UnknownCommand();    //In the case of anything else, send: Unknown Command
    }
    break;
  }
}
