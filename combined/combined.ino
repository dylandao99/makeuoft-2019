int rotary = A0;
int rotaryData;
int oldRotaryData = 0;
int buzzer = A1;
char readByte1 = 0;
char readByte2 = 0;
int writeBuzzer = 0;

void setup(){
  pinMode(rotary, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  rotaryData = analogRead(rotary);
  if (oldRotaryData != rotaryData){
    Serial.write(rotaryData);
    oldRotaryData = rotaryData;
  }
  if (Serial.available() > 0){
    readByte1 = Serial.read();
    readByte2 = Serial.read();
    writeBuzzer = 0;
    writeBuzzer = readByte1<<2 & readByte2>>6;
    analogWrite(buzzer, writeBuzzer);
    delay(2000);
  }
}
