int sensorPin = 0;
int ledPin = 9;
int sensorValue = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int value = analogRead(sensorPin) / 4; // AnalogRead - 0 - 1024, analogWrite - 0 - 255. Thats why divide by 4.
  analogWrite(ledPin, value);
}
