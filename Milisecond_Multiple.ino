void WaitTillMsMultiple(int MsMultiple) {
  while (true) {
    {
//      Serial.println(millis());
      if (millis() % MsMultiple == 0)  //test whether the period has elapsed
      {
        break;
      }
    }
  }
}
