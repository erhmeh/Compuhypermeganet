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
  int servoAngles_[3];

private:
  double matrix[3][3];
  const double frontServoVec_[3] = {0.0, -1.0, 0.0};
  const double leftServoVec_[3] = {1.0, -1.0, 0.0};
  const double rightServoVec_[3] = {-1.0, 1.0, 0.0};
  const double platHeight_[3] = {0.0, 0.0, 3.0};
  void attachServos(int *pins);
  double calcAngle1_;
  double calcAngle2_;
  double calcAngle3_;
  double vecSum1_[3];
  double vecSum2_[3];
  double vecSum3_[3];
  double liFrontMag_;
  double liLeftMag_;
  double liRightMag_;
  Servo frontServo_;
  Servo leftServo_;
  Servo rightServo_;
};

#endif