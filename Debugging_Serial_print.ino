extern float PosR;
extern char Command[];
extern int Feedrate;

void Debugging_Serial_print(){
  Serial.println("");
  Serial.println("--------------Debugging Section-------------------");
  Serial.print("Received Command: ");
  Serial.println(Command);
  Serial.print("Understood Command: ");
  Serial.print(Command[0]);
  Serial.println(CommandNumberExtractor());
  Serial.print("R Position = ");
  Serial.println(PosR);
  Serial.print("Feedrate = ");
  Serial.println(Feedrate);
  Serial.println("--------------------------------------------------");
  Serial.println("");
}
