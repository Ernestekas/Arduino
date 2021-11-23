/*
 * Created by ArduinoGetStarted, https://arduinogetstarted.com
 *
 * Arduino - Ultrasonic Sensor HC-SR04
 *
 * Wiring: Ultrasonic Sensor -> Arduino:
 * - VCC  -> 5VDC
 * - TRIG -> Pin 9
 * - ECHO -> Pin 8
 * - GND  -> GND
 *
 * Tutorial is available here: https://arduinogetstarted.com/tutorials/arduino-ultrasonic-sensor.php
 */

int trigPin = 9;    // TRIG pin
int echoPin = 8;    // ECHO pin

int counter = 0;

float duration_us, distance_cm, avg_distance_cm;
float distances_cm[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


void setup() {
  // begin serial port
  Serial.begin (9600);

  // configure the trigger pin to output mode
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = 0.017 * duration_us;
  avg_distance_cm = updateAverage(distances_cm, distance_cm);
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
  Serial.print("Average distance: ");
  Serial.print(avg_distance_cm);
  Serial.println(" cm");
  
  delay(1000);
}

float updateAverage(float oldDistances[10], float newDistance)
{
  float average = 0;
  float sum = 0;
  for(int i = sizeof(oldDistances) - 1; i > -1; i--)
  {
    if(i > 0)
    {
      oldDistances[i] = oldDistances[i - 1];
    }
    else
    {
      oldDistances[i] = newDistance;
    }
  }
  
  for(int i = 0; i < sizeof(oldDistances); i++)
  {
    sum += oldDistances[i];
  }
  average = sum / sizeof(oldDistances);
  return average;
}
