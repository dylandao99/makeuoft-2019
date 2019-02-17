int rotary = A0;
int rotaryData;
int oldRotaryData = 0;
int buzzer = 11;
char readByte1 = 0;
char readByte2 = 0;
int writeBuzzer = 0;

void setup(){
  pinMode(rotary, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  if (Serial.available() > 0){
    readByte1 = Serial.read();
    Serial.print('a');
    Serial.print(readByte1, BIN);
    Serial.print('\n');
    readByte2 = Serial.read();
    Serial.print('b');
    Serial.print(readByte2, BIN);
    Serial.print('\n');
    writeBuzzer = 0;
    writeBuzzer = readByte1<<2 & readByte2>>6;
    Serial.print('c');
    Serial.print(writeBuzzer, BIN);
    Serial.print('\n');
    analogWrite(buzzer, writeBuzzer);
    delay(100);
  }
}
