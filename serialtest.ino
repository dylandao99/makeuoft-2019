int buzzer = 3;

void setup(){
	pinMode(buzzer, OUTPUT);
}

void loop(){
	if (Serial.available() > 0){
		digitalWrite(buzzer, HIGH);
		delay(2000);
	}
}
