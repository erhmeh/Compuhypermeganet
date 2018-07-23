#ifndef platform_H
#define platform_H

#include <Arduino.h>
#include <Servo.h>

class platform
{
public:
  void moveTo(int servo, int angle);
  void calculateAngles(float pitch, float roll);
  void initPlatform(int *pins);
  void updateServos();
  int angles_[3];

private:
  void attachServos(int *pins);
  Servo frontServo_;
  Servo leftServo_;
  Servo rightServo_;
};

#endif