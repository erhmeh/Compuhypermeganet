/* RoboCamp Self Leveling Robot
 * @author Jamin Early
 * @date July 2018
 *
 * Beerware
 */

#include "Arduino.h"
#include "FlexiTimer2.h"
#include "MatrixMath.h"
#include "SD.h"
#include "SPI.h"
#include "adxl337.h"
#include "platform.h"
#include "quadruped.h"
#include "SDConfigFile.h"

File alfredConfig;

// Remove the Serial writing for faster processing
#define DEBUG_PRINT(x) Serial.print(x)
#define DEBUG_WRITE(x) Serial.write(x)
#define DEBUG_PRINTDEC(x) Serial.print(x, DEC)
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINTLNHEX(x) Serial.println(x, HEX)

// IO pins

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

/* Digital IO Testing Pins */
#define D1 13
#define D2 14

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

/* store current and target coordinates for legs */
position_t current_coordinates[8];
position_t target_coordinates[8];

// Initialises quadruped and attaches servos
void initQuadruped()
{
  int pins[] = {L4_1, L4_2, L3_1, L3_2, L2_1, L2_2, L1_1, L1_2};
  quad.setPins(pins);
  quad.attachServos();
  quad.startingPosition();
}

// Initialises the platform servos and resets them to 45 degrees
void initPlatform()
{
  int pins[] = {S1, S2, S3};
  plat.initPlatform(pins);
}

// Updates the acceleration array when called by the timer
void tick()
{
  digitalWrite(D1, HIGH);
  accel.getAccel(recentAccel);
  plat.calculateAngles(accel.getPitch(recentAccel), accel.getRoll(recentAccel));
  DEBUG_PRINT("Servo Angles: ");
  DEBUG_PRINT(" ");
  DEBUG_PRINT(plat.servoAngles_[0]);
  DEBUG_PRINT(" ");
  DEBUG_PRINT(plat.servoAngles_[1]);
  DEBUG_PRINT(" ");
  DEBUG_PRINTLN(plat.servoAngles_[2]);
  plat.updateServos();
  digitalWrite(D1, LOW);
}

// main setup
void setup()
{
  Serial.begin(9600);
  delay(2000);
  Serial.print("Initializing SD card...");

  if (!SD.begin(BUILTIN_SDCARD))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  initPlatform();
  randomSeed(analogRead(0));
  initQuadruped();
  FlexiTimer2::set(20, 1.0 / 1000, tick); // call every 200 1ms "ticks" (50hz)
  FlexiTimer2::start();                   // start the timer
}

// main loop
void loop() {}
