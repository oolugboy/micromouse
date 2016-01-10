#include <Servo.h>
#include "NanomouseMotors.h";
#include "NanomouseSensors.h";

const byte ledPin = 13;
const byte buttonPin = 9;

NanomouseMotors motors;

NanomouseSensors<4, A7, 3, A6, 2, A5> sensors;

void setup()
{
  motors.attach(6, 5);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  sensors.configure();

  Serial.begin(9600);

  while (digitalRead(buttonPin))
  {}
}

void loop()
{
    sensors.sense();
    motors.forwardProportional(sensors.right-sensors.left);
    avoid(state());
}

byte state()
{
  // threshold where obstacle is dectected, may need to be adjusted
    int threshold = 30;
    byte event = 0;

    sensors.sense();

    if(sensors.front > threshold){event += 1;}
    if(sensors.left > threshold){event += 2;}
    if(sensors.right > threshold){event += 4;}

    return event;
}

void avoid(byte event)
{
    switch(event)
    {
      case 1: //Front sensor triggered
        if(random(2))
        {
          motors.turn(LEFT,90);
        }
        else
        {
          motors.turn(RIGHT,90);
        }
        sensors.initialize();
        break;
      case 2: //Left sensor triggered
        motors.turn(RIGHT,45);
        sensors.initialize();
        break;
      case 4: //Right sensor triggered
        motors.turn(LEFT,45);
        sensors.initialize();
        break;
      default:
        motors.forward();
        break;
    }
}

