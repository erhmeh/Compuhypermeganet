/* RoboCamp Self Leveling Robot
 * @author Jamin Early
 * @date July 2018
 *
 * Beerware
 */

#include "Arduino.h"
#include "adxl337.h"
#include "quadruped.h"
#include "FlexiTimer2.h"
#include "platform.h"

// Remove the Serial writing for faster processing
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_WRITE(x) Serial.write(x)
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINTLNHEX(x) Serial.println(x, HEX)

// IO pins
/* Accelerometer Pins */
#define ADXL337_X_PIN 12
#define ADXL337_Y_PIN 13
#define ADXL337_Z_PIN 14

/* Quad Servo Pins */
#define L4_1 0
#define L4_2 1
#define L3_1 2
#define L3_2 3
#define L2_1 4
#define L2_2 5
#define L1_1 6
#define L1_2 7

/* Platform Servo Pins*/
#define S1 12
#define S2 24
#define S3 25

// Prototype functions
void initADXL337();
void initQuadruped();
void initPlatform();
void updateAcceleration();

adxl337 accel;  // Accelerometer object
quadruped quad; // Quadruped object
platform plat;  // Platform object

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

// Initialises quadruped and attaches servos
void initQuadruped()
{
    int pins[] = {L4_1, L4_2, L3_1, L3_2, L2_1, L2_2, L1_1, L1_2};
    quad.setPins(pins);
    quad.attachServos();
}

// Initialises the platform servos and resets them to 45 degrees
void initPlatform()
{
    int pins[] = {S1, S2, S3};
    plat.initPlatform(pins);
}

// Updates the acceleration array when called by the timer
void updateAcceleration()
{
    accel.getAccel(recentAccel);
}
/******************************************************
 *                  TEST FUNCTION
 * ***************************************************/
void servoPlatTest(){

}

// main setup
void setup()
{
    Serial.begin(9600); // really fast serial ftw
    // initQuadruped();
    // FlexiTimer2::set(100, 1.0 / 1000, updateAcceleration); // call every 100 1ms "ticks"
    // FlexiTimer2::start();                                  // start the timer
}

// main loop
void loop()
{
}
