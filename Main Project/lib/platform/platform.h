#ifndef platform_H
#define platform_H

#include <Arduino.h>
#include <Servo.h>

class platform
{
  public:
    void attachServos(int *pins);
    void moveTo(int servo, int angle);
  private:
    Servo frontServo_;
    Servo leftServo_;
    Servo rightServo_;
};

#endif