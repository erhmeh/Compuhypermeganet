// Header file for the Accelerometer. Further commenting on functionality in adxl337.cpp

#ifndef adxl337_H
#define adxl337_H

#include <Arduino.h>

class adxl337 {
public:
void setPins(int x, int y, int z);
void getAccel(float * result);
float getPitch(float * accel);
float getRoll(float * accel);
private:
void takeRawMeasurement();
void takeScaledMeasurement();
float mapf(float x, float in_min, float in_max, float out_min, float out_max);
int scale = 3; // 3 (±3g) for adxl337
int xPin_;
int yPin_;
int zPin_;
int xRaw_;
int yRaw_;
int zRaw_;
float xScaled_;
float yScaled_;
float zScaled_;
};

#endif // ifndef adxl337_H
