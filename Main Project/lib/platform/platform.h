#ifndef platform_H
#define platform_H

#include <Arduino.h>
#include <MatrixMath.h>
#include <Servo.h>

class platform
{
public:
  void moveTo(int servo, int angle);
  void calculateAngles(double pitch, double roll);
  void initPlatform(int *pins);
  void updateServos();
  int angles_[3];

private:
  double matrix[3][3];
  const double frontServoDist_ = 1.0;
  const double leftServoDist_ = 1.0;
  const double rightServoDist_ = 1.0;
  const double platHeight_ = 1.0;
  void attachServos(int *pins);
  Servo frontServo_;
  Servo leftServo_;
  Servo rightServo_;
};

#endif