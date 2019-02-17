int rotary = A0;
int rotaryData;
int oldRotaryData = 0;
int buzzer = 11;
unsigned char readByte1 = 0;
unsigned char readByte2 = 0;
char writeBuzzer[2];
int actualWrite;
String inString = "";

void setup(){
  pinMode(rotary, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

//void loop(){
//  if (Serial.available() > 0){
//    readByte1 = Serial.read();
//    Serial.println('a');
//    Serial.println(readByte1, BIN);
//    readByte2 = Serial.read();
//    Serial.println('b');
//    Serial.println(readByte2, BIN);
//    writeBuzzer = 0;
    
//    writeBuzzer = readByte1<<2 & readByte2>>6;
//    Serial.print("available");
//    Serial.print(Serial.available());
//    Serial.print('\n');
//    Serial.readBytes(writeBuzzer, 2);
//    Serial.print("write");
//    Serial.print('\n');
//    Serial.print(writeBuzzer[0]);
//    Serial.print('\n');
//    Serial.print(writeBuzzer[1]);
//    Serial.print('\n');
//    actualWrite = (writeBuzzer[0]<<2 & 0x3fc) | writeBuzzer[1]>>6;
//    Serial.print(actualWrite);
//    Serial.print('\n');
//    analogWrite(buzzer, actualWrite);
//    delay(1000);
//  }
//}
void loop() {
  // Read serial input:
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    if (isDigit(inChar)) {
      // convert the incoming byte to a char and add it to the string:
      inString += (char)inChar;
    }
    // if you get a newline, print the string, then the string's value:
    if (inChar == '\n') {
      Serial.print("Value:");
      Serial.println(inString.toInt());
      Serial.print("String: ");
      Serial.println(inString);
      analogWrite(buzzer, inString.toInt());
      // clear the string for new input:
      inString = "";
    }
  }
}
