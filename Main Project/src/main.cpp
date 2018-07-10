/* RoboCamp Self Leveling Robot
 * @author Jamin Early
 * @date July 2018
 *
 * Beerware
 */

#include "Arduino.h"
#include "adxl337.h"

// Remove the Serial writing for faster processing
#define DEBUG_PRINT(x)      Serial.print(x)
#define DEBUG_WRITE(x)      Serial.write(x)
#define DEBUG_PRINTDEC(x)   Serial.print(x, DEC)
#define DEBUG_PRINTLN(x)    Serial.println(x)
#define DEBUG_PRINTLNHEX(x) Serial.println(x, HEX)

// IO pins
#define ADXL337_X_PIN 12
#define ADXL337_Y_PIN 13
#define ADXL337_Z_PIN 14

adxl337 accel; // Accelerometer object

/* Parse this array to the the accelerometer class to fill it with most recent
   acceleration readings
 * [0] -> X; [1] -> Y; [2] -> Z
 * Note that these values are scaled not raw
 */
float recentAccel[3];

// Initialises the accelerometer pins
void initADXL337()
{
    accel.setPins(ADXL337_X_PIN, ADXL337_Y_PIN, ADXL337_Z_PIN);
}

// main setup
void setup()
{
    Serial.begin(115200);                                                             // really fast serial ftw
}

// main loop
void loop()
{
}
