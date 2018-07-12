#include "adxl337.h"
#include "Arduino.h"

// Setter method for pins
void adxl337::setPins(int x, int y, int z)
{
    xPin_ = x;
    yPin_ = y;
    zPin_ = z;
}

// Takes an analog reading of each pin and sets their values
void adxl337::takeRawMeasurement()
{
    xRaw_ = analogRead(xPin_);
    yRaw_ = analogRead(yPin_);
    zRaw_ = analogRead(zPin_);
}

// Scales the raw analogReadings into non-abstract values
void adxl337::takeScaledMeasurement()
{
    takeRawMeasurement();
    xScaled_ = mapf(xRaw_, 0, 675, -scale, scale);
    yScaled_ = mapf(yRaw_, 0, 675, -scale, scale);
    zScaled_ = mapf(zRaw_, 0, 675, -scale, scale);
}

void adxl337::getAccel(float * result)
{
    takeScaledMeasurement();
    result[0] = xScaled_;
    result[1] = yScaled_;
    result[2] = zScaled_;
}

// Map function (similar to native arduino) but using floating point values
float adxl337::mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}