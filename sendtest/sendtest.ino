int rotary = A0;
int rotaryData;
int oldRotaryData = 0;

void setup(){
	pinMode(rotary, INPUT);
	Serial.begin(9600);
}

void loop(){
	rotaryData = analogRead(rotary);
	if (oldRotaryData != rotaryData){
		Serial.write(rotaryData);
		oldRotaryData = rotaryData;
	}
}
