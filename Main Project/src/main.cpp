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
#include "SDConfigFile.h"
#include "SPI.h"
#include "adxl337.h"
#include "platform.h"
#include "quadruped.h"

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

/* Stores config values*/
bool quadEnable = false;
bool platEnable = false;
bool timerPeriod = 20;

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

// Loads the configuration file from the SD card
void loadConfig()
{
  while (!SD.begin(BUILTIN_SDCARD))
  {
    DEBUG_PRINTLN("No SD-card.");
    DEBUG_PRINTLN("Cannot find SD card. Please check that it is secured.");
  }
  SDConfigFile cfg;
  if (!cfg.begin("alfred.cfg", 127))
  {
    DEBUG_PRINTLN("Failed to open config");
    delay(1);
    if (!cfg.begin("alfred.cfg", 127))
    {
      DEBUG_PRINTLN("Config file cannot be opened. Please regenerate it.");
    }
  }
  while (cfg.readNextSetting())
  {
    if (cfg.nameIs("timerPeriod"))
    {
      timerPeriod = cfg.getIntValue();
    }
    if (cfg.nameIs("quadEnable"))
    {
      quadEnable = cfg.getBooleanValue();
    }
    if (cfg.nameIs("platEnable"))
    {
      platEnable = cfg.getBooleanValue();
      DEBUG_PRINTLN("ON");
    }
  }
  if (platEnable || quadEnable)
  {
    cfg.end();
    return;
  }
}

// Main code to execute (at 50hz)
void tick()
{
  digitalWrite(D1, HIGH);
  if (true)
  {
    accel.getAccel(recentAccel);
    plat.calculateAngles(accel.getPitch(recentAccel),
                         accel.getRoll(recentAccel));
    DEBUG_PRINT("Servo Angles: ");
    DEBUG_PRINT(" ");
    DEBUG_PRINT(plat.servoAngles_[0]);
    DEBUG_PRINT(" ");
    DEBUG_PRINT(plat.servoAngles_[1]);
    DEBUG_PRINT(" ");
    DEBUG_PRINTLN(plat.servoAngles_[2]);
    plat.updateServos();
  }
  digitalWrite(D1, LOW);
}

// main setup
void setup()
{
  Serial.begin(9600);
  // delay(5000);
  // loadConfig();
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  initPlatform();
  if (platEnable)
  {
  }
  // pinMode(3, OUTPUT);
  delay(2000);
  FlexiTimer2::set(250, 1.0 / 1000, tick); // call every 200 1ms "ticks" (50hz)
  FlexiTimer2::start();                    // start the timer
}

// main loop
void loop() {}
