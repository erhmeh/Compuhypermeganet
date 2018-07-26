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
  void attachServos(int *pins);
  double matrix[3][3];

  const double frontServoHornVec_[3] = { - 90.23, 0.0, 4.02}; //a1_0
  const double leftServoHornVec_[3] = {45.12, 78.15, 4.02};  //a2_0
  const double rightServoHornVec_[3] = {45.12, -78.15, 4.02};//a3_0

  const double frontServoVec_[3] = { - 84.5, 0.0, 0.0}; //b1_0
  const double leftServoVec_[3] = {42.25, 73.18, 0.0};  //b2_0
  const double rightServoVec_[3] = {42.25, -73.18, 0.0};//b3_0

  const double frontPlatVec_[3] = { - 84.5, 0.0, 122.1}; //p1_0
  const double leftPlatVec_[3] = {42.25, 73.18, 122.1};  //p2_0
  const double rightPlatVec_[3] = {42.25, -73.18, 122.1};//p3_0
  
  const double platHeight_[3] = {0.0, 0.0, 122.1};      //T_0
  const double armLength_ = 70.0;                       //a_0
  const double pistonLength_ = 98.99;                   //s_0


  
  double calcAngle1_;
  double calcAngle2_;
  double calcAngle3_;
  double vecSum1_[3];
  double vecSum2_[3];
  double vecSum3_[3];
  double M1_;
  double M2_;
  double M3_;
  double N1_;
  double N2_;
  double N3_;
  double alfa1_;
  double alfa2_;
  double alfa3_;

  
  double liFrontMag_;
  double liLeftMag_;
  double liRightMag_;
  double e1_;
  double e2_;
  double e3_;
  Servo frontServo_;
  Servo leftServo_;
  Servo rightServo_;
};

#endif