int ledPin = 9;
int i = 0;
int lightLevel = 0;

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
    Serial.println("lightLevel should be 0");
  }

  analogWrite(ledPin, lightLevel);
  delay(50);
  
  Serial.print("i: ");
  Serial.print(i);
  Serial.print(" ");
  Serial.print("lightLevel: ");
  Serial.print(lightLevel);
  Serial.println();
}
