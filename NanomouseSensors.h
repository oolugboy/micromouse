#include <Arduino.h>

template <byte leftEmitter, byte leftDetector,
          byte frontEmitter, byte frontDetector,
          byte rightEmitter, byte rightDetector>

class NanomouseSensors
{
  private:
    // stores values from when emitters are off
    int frontAmbient;
    int leftAmbient;
    int rightAmbient;

    // stores values from when emitters are on
    int frontCombined;
    int leftCombined;
    int rightCombined;

    // stores value from ambient light filtered out
    int frontReflected;
    int leftReflected;
    int rightReflected;

    int frontTotal;
    int leftTotal;
    int rightTotal;
    static const byte numReadings = 20;
    byte index;

    int frontReadings[numReadings];
    int leftReadings[numReadings];
    int rightReadings[numReadings];

    int frontSmoothed;
    int leftSmoothed;
    int rightSmoothed;


  public:
    int front;
    int left;
    int right;

    void configure()
    {
      pinMode(frontEmitter, OUTPUT);
      pinMode(leftEmitter, OUTPUT);
      pinMode(rightEmitter, OUTPUT);
    }

    void sense()
    {
      digitalWrite(frontEmitter, HIGH);
      digitalWrite(leftEmitter, HIGH);
      digitalWrite(rightEmitter, HIGH);
      delay(10);

      frontCombined = analogRead(frontDetector);
      leftCombined = analogRead(leftDetector);
      rightCombined = analogRead(rightDetector);

      digitalWrite(frontEmitter, LOW);
      digitalWrite(leftEmitter, LOW);
      digitalWrite(rightEmitter, LOW);
      delay(10);

      frontAmbient = analogRead(frontDetector);
      leftAmbient = analogRead(leftDetector);
      rightAmbient = analogRead(rightDetector);

      frontReflected = frontCombined - frontAmbient;
      leftReflected = leftCombined - leftAmbient;
      rightReflected = rightCombined - rightAmbient;

      //smoothing process
      frontTotal -= frontReadings[index];
      leftTotal -= leftReadings[index];
      rightTotal -= rightReadings[index];

      frontReadings[index] = frontReflected;
      leftReadings[index] = leftReflected;
      rightReadings[index] = rightReflected;

      frontTotal += frontReadings[index];
      leftTotal += leftReadings[index];
      rightTotal += rightReadings[index];

      index += 1;

      if (index >= numReadings) {
        index = 0;
      }

      frontSmoothed = frontTotal / numReadings;
      leftSmoothed = leftTotal / numReadings;
      rightSmoothed = rightTotal / numReadings;

      front = frontSmoothed;
      left = leftSmoothed;
      right = rightSmoothed;
    }

    void view()
    {
      Serial.print(left);
      Serial.print("\t");
      Serial.print(front);
      Serial.print("\t");
      Serial.println(right);
    }

    void initialize()
    {
      for (byte i = 0; i < numReadings; i++)
      {
        sense();
      }
    }
};

