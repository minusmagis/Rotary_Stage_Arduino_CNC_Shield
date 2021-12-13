extern const int TRIGGER_PIN;

void Trigger(){                           // Set the trigger pin to high for 1 ms
  digitalWrite(TRIGGER_PIN,HIGH);
  delay(10);
  digitalWrite(TRIGGER_PIN,LOW);
//  Serial.println("Trigger Event");
}
