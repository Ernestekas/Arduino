int ledPins[] = {2,3,5,6,7,8,9};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 7; i++)
  {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  LightLedsStepByStep();
}

void LightLedsStepByStep()
{
  int delayTime = 500;

  for(int i = 0; i < 7; i++)
  {
    digitalWrite(ledPins[i], HIGH);
    delay(delayTime);
  }

  for(int i = 0; i < 3; i++)
  {
    for(int j = 0; j < 7; j++)
    {
      digitalWrite(ledPins[j], LOW);
    }
    delay(delayTime);
    for(int j = 0; j < 7; j++)
    {
      digitalWrite(ledPins[j], HIGH);
      delay(1);
    }
    delay(delayTime);
  }

  for(int i = 6; i > -1; i--)
  {
    digitalWrite(ledPins[i], LOW);
    delay(delayTime);
  }
}
