// Header file for the Accelerometer. Further commenting on functionality in
// adxl337.cpp

#ifndef adxl337_H
#define adxl337_H

#include <Arduino.h>

class adxl337
{
public:
  void getAccel(float *result);
  float getPitch(float *accel);
  float getRoll(float *accel);

private:
  int xRaw_;
  int yRaw_;
  int zRaw_;
  void takeRawMeasurement();
  void takeScaledMeasurement();
  float mapf(float x, float in_min, float in_max, float out_min, float out_max);
  float scale = 3.0; // 3 (±3g) for adxl337
  float xScaled_;
  float yScaled_;
  float zScaled_;
  float xRawMin_ = 202.0;
  float xRawMax_ = 823.0;
  float yRawMin_ = 194.0;
  float yRawMax_ = 821.0;
  float zRawMin_ = 194.0;
  float zRawMax_ = 812.0;
};

#endif // ifndef adxl337_H
