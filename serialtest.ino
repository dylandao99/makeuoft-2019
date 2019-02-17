int buzzer = 3;

void setup(){
	pinMode(buzzer, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	if (Serial.available() > 0){
		digitalWrite(buzzer, HIGH);
		delay(2000);
	}
}
