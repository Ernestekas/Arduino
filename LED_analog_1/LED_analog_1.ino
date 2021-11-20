int ledPin = 9;
int i = 0;
int lightLevel = 0;
int delayTime = 50;


void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(ledPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if(i < 256)
  {
    lightLevel = i;
    i++;
  }

  if(lightLevel == 255)
  {
    lightLevel = 0;
    delayTime = 10000;
  }

  analogWrite(ledPin, lightLevel);
  delay(delayTime);
  Serial.print(i, " ", lightLevel);
  Serial.println():
}
