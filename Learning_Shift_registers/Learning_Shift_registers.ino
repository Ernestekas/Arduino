int latchPin = 5;  // Latch pin of 74HC595 is connected to Digital pin 5
int clockPin = 6; // Clock pin of 74HC595 is connected to Digital pin 6
int dataPin = 4;  // Data pin of 74HC595 is connected to Digital pin 4

// HC-SR04 define pins.
int trigPin = 9;
int echoPin = 8;

float distance_cm;

int startingLed = 3;

byte leds = 0;    // Variable to hold the pattern of which LEDs are currently turned on or off

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup() 
{
  // Set all the pins of 74HC595 as OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  
  // HC-SR04 assign pins.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Serial.begin(9600);
}

/*
 * loop() - this function runs over and over again
 */
void loop() 
{
  distance_cm = GetDistance();
  updateShiftRegister();
  ShowDistance(startingLed, distance_cm);
}

/*
 * updateShiftRegister() - This function sets the latchPin to low, then calls the Arduino function 'shiftOut' to shift out contents of variable 'leds' in the shift register before putting the 'latchPin' high again.
 */
void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

float GetDistance()
{
  float distance;
  float duration;
  float distances[3];
  float minValue, maxValue;
  
  for(int i = 0; i < 3; i++)
  {
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = 0.017 * duration;
    distances[i] = distance;
    Serial.print("Measured distance: ");
    Serial.println(distance);
    
    if(i == 1)
    {
      if(distances[1] < distances[0])
      {
        float temp = distances[0];
        distances[0] = distances[1];
        distances[1] = temp;
      }
    }
    if(i == 2)
    {
      if(distances[2] < distances[1])
      {
        float temp = distances[1];
        distances[1] = distances[1];
        distances[2] = temp;
        if(distances[2] < distances[0])
        {
          temp = distances[0];
          distances[0] = distances[1];
          distances[1] = temp;
        }
      }
    }
  }

  distance = distances[1];
  Serial.print("Median distance: ");
  Serial.println(distance);
  return distance;
}

void ShowDistance(int startingLed, float measuredDistance)
{
  int maxLed = startingLed;
  updateShiftRegister();
  delay(100);
  if(measuredDistance < 10)
  {
    maxLed = 7;
  }
  else if(measuredDistance < 20)
  {
    maxLed = 6;
    //bitClear(leds, 7);
  }
  else if(measuredDistance < 30)
  {
    maxLed = 5;
  }
  else if(measuredDistance < 40)
  {
    maxLed = 4;
  }
  else
  {
    maxLed = 3;
  }
  for(int i = 7; i > maxLed; i--)
  {
    bitClear(leds, i);
  }
  for(int i = 0; i < maxLed + 1; i++)
  {
    bitSet(leds, i);
  }
  delay(100);
}
