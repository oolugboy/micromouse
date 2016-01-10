#include <Arduino.h>
#include <Servo.h>

#define RIGHT -1
#define LEFT 1

class NanomouseMotors {
  private:
    Servo leftServo;
    Servo rightServo;
    static const byte power = 250;

  public:

    void attach(byte leftMotor, byte rightMotor)
    {
      leftServo.attach(leftMotor);
      rightServo.attach(rightMotor);
    }
    float turnConst = 5.5555555;

    void stop(int time = 200)
    {
      leftServo.writeMicroseconds(1500);
      rightServo.writeMicroseconds(1500);
      delay(time);
    }

    void backward()
    {
      leftServo.writeMicroseconds(1500 + power);
      rightServo.writeMicroseconds(1500 - power);
    }

    void forward()
    {
      leftServo.writeMicroseconds(1500 - power);
      rightServo.writeMicroseconds(1500 + power);
    }

    void forwardTime(unsigned int time)
    {
      forward();
      delay(time);
      stop();
    }


    void turn(int direction, int degrees)
    {
      leftServo.writeMicroseconds(1500 + power * direction);
      rightServo.writeMicroseconds(1500 + power * direction);
      delay(degrees * turnConst);
      stop();
    }

    void polygon(int edges, int size)
    {
      int angle = 180 - ((edges - 2) * 180) / edges;
      for (int i = 0; i < edges; i++) {
        forwardTime(size * 500);
        turn(LEFT, angle);
      }
    }

    void forwardProportional(int error)
    {
      leftServo.writeMicroseconds(1500 - power - error);
      rightServo.writeMicroseconds(1500 + power - error);
    }
};
