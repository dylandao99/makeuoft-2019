int buzzer = 3;
char data = 'a';

void setup(){
	pinMode(buzzer, OUTPUT);
	Serial.begin(9600);
}

void loop(){
	if (Serial.available() > 0){
	data = Serial.read();
		if (data == '1'){
			digitalWrite(buzzer, HIGH);
			}
		else if (data == '0'){
			digitalWrite(buzzer, LOW);
		}
	}
}
