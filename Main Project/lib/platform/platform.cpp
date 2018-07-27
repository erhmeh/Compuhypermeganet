#include "platform.h"
#include <math.h>

// Initialises the platform servos, attaches them and then moves them to 90
// degrees
void platform::initPlatform(int *pins)
{
    attachServos(pins);
    for (int i = 1; i <= 3; i++)
    {
        moveTo(i, 35);
    }
    matrix[1][0] = 0.0;
    delay(2000);
}

// Attaches pins. Parse a int[3] with the pin numbers in the order of 1 ->
// front, 2 -> left, 3 -> right
void platform::attachServos(int *pins)
{
    frontServo_.attach(pins[0]);
    leftServo_.attach(pins[1]);
    rightServo_.attach(pins[2]);
}

// Moves a servo to a specified angle 1 -> front, 2 -> left, 3 -> right
void platform::moveTo(int servo, int angle)
{
    switch (servo)
    {
    case 1:
        frontServo_.write(angle);
        break;
    case 2:
        leftServo_.write(angle);
        break;
    case 3:
        rightServo_.write(angle);
        break;
    default:
        break;
    }
}

// Recalculates angles and populates array with target angles
void platform::calculateAngles(double pitch, double roll)
{
    double pitchR = pitch * 1000 / 57296;
    double rollR = roll * 1000 / 57296;

    Serial.print("Pitch: ");
    Serial.println(pitch);
    Serial.print("Roll: ");
    Serial.println(roll);
    // The full rotation matrix of the Platform relative to the Base (p-R-b)(1)
    matrix[0][0] = cos(pitchR);
    matrix[0][1] = sin(pitchR) * sin(rollR);
    matrix[0][2] = cos(rollR) * sin(rollR);
    matrix[1][0] = 0.0;
    matrix[1][1] = cos(rollR);
    matrix[1][2] = -sin(rollR);
    matrix[2][0] = -sin(pitchR);
    matrix[2][1] = cos(pitchR) * sin(rollR);
    matrix[2][2] = cos(rollR) * cos(pitchR);

    //(p-i)*(p-R-b) (2-1)
    vecSum1_[0] = matrix[0][0] * frontPlatVec_[0] +
                  matrix[0][1] * frontPlatVec_[1] +
                  matrix[0][2] * frontPlatVec_[2];
    vecSum1_[1] = matrix[1][0] * frontPlatVec_[0] +
                  matrix[1][1] * frontPlatVec_[1] +
                  matrix[1][2] * frontPlatVec_[2];
    vecSum1_[2] = matrix[2][0] * frontPlatVec_[0] +
                  matrix[2][1] * frontPlatVec_[1] +
                  matrix[2][2] * frontPlatVec_[2];
    vecSum2_[0] = matrix[0][0] * leftPlatVec_[0] +
                  matrix[0][1] * leftPlatVec_[1] + matrix[0][2] * leftPlatVec_[2];
    vecSum2_[1] = matrix[1][0] * leftPlatVec_[0] +
                  matrix[1][1] * leftPlatVec_[1] + matrix[1][2] * leftPlatVec_[2];
    vecSum2_[2] = matrix[2][0] * leftPlatVec_[0] +
                  matrix[2][1] * leftPlatVec_[1] + matrix[2][2] * leftPlatVec_[2];
    vecSum3_[0] = matrix[0][0] * rightPlatVec_[0] +
                  matrix[0][1] * rightPlatVec_[1] +
                  matrix[0][2] * rightPlatVec_[2];
    vecSum3_[1] = matrix[1][0] * rightPlatVec_[0] +
                  matrix[1][1] * rightPlatVec_[1] +
                  matrix[1][2] * rightPlatVec_[2];
    vecSum3_[2] = matrix[2][0] * rightPlatVec_[0] +
                  matrix[2][1] * rightPlatVec_[1] +
                  matrix[2][2] * rightPlatVec_[2];

    ////////////(3)

    vec2Sum1_[0] = platHeight_[0] + vecSum1_[0];
    vec2Sum1_[1] = platHeight_[1] + vecSum1_[1];
    vec2Sum1_[2] = platHeight_[2] + vecSum1_[2];
    vec2Sum2_[0] = platHeight_[0] + vecSum2_[0];
    vec2Sum2_[1] = platHeight_[1] + vecSum2_[1];
    vec2Sum2_[2] = platHeight_[2] + vecSum2_[2];
    vec2Sum3_[0] = platHeight_[0] + vecSum2_[0];
    vec2Sum3_[1] = platHeight_[1] + vecSum3_[1];
    vec2Sum3_[2] = platHeight_[2] + vecSum3_[2];

    vec3Sum1_[0] = vec2Sum1_[0] - frontServoVec_[0];
    vec3Sum1_[1] = vec2Sum1_[1] - frontServoVec_[1];
    vec3Sum1_[2] = vec2Sum1_[2] - frontServoVec_[2];
    vec3Sum2_[0] = vec2Sum2_[0] - leftServoVec_[0];
    vec3Sum2_[1] = vec2Sum2_[1] - leftServoVec_[11];
    vec3Sum2_[2] = vec2Sum2_[2] - leftServoVec_[2];
    vec3Sum3_[0] = vec2Sum3_[0] - rightServoVec_[0];
    vec3Sum3_[1] = vec2Sum3_[1] - rightServoVec_[1];
    vec3Sum3_[2] = vec2Sum3_[2] - rightServoVec_[2];
    /*
    M1_ = 2 * 70 * (vecSum1_[2] - frontServoVec_[2]);
    M2_ = 2 * 70 * (vecSum2_[2] - leftServoVec_[2]);
    M3_ = 2 * 70 * (vecSum3_[2] - rightServoVec_[2]);

    N1_ = 2 * 70 *
          (cos((60.0 * 1000.0) / 57296.0) * (vecSum1_[0] - frontServoVec_[0]) +
           sin((60.0 * 1000.0) / 57296.0) * (vecSum1_[1] - frontServoVec_[1]));
    N2_ = 2 * 70 *
          (cos((60.0 * 1000.0) / 57296.0) * (vecSum2_[0] - leftServoVec_[0]) +
           sin((60.0 * 1000.0) / 57296.0) * (vecSum2_[1] - leftServoVec_[1]));
    N3_ = 2 * 70 *
          (cos((60.0 * 1000.0) / 57296.0) * (vecSum3_[0] - rightServoVec_[0]) +
           sin((60.0 * 1000.0) / 57296.0) * (vecSum3_[1] - rightServoVec_[1]));
    double i1 = sqrt(vec3Sum1_[0] * vec3Sum1_[0] + vec3Sum1_[1] * vec3Sum1_[1] +
                     vec3Sum1_[2] * vec3Sum1_[2]);
    alfa1_ = asin(i1 / (sqrt((M1_ * M1_) + (N1_ * N1_))) - atan(N1_ / M1_)) *
             57296 / 1000;
    double i2 = sqrt(vec3Sum2_[0] * vec3Sum2_[0] + vec3Sum2_[1] * vec3Sum2_[1] +
                     vec3Sum2_[2] * vec3Sum2_[2]);
    alfa2_ = asin(i2 / (sqrt((M2_ * M2_) + (N2_ * N2_))) - atan(N2_ / M2_)) *
             57296 / 1000;
    double i3 = sqrt(vec3Sum3_[0] * vec3Sum3_[0] + vec3Sum3_[1] * vec3Sum3_[1] +
                     vec3Sum3_[2] * vec3Sum3_[2]);
    alfa3_ = asin(i3 / sqrt((M3_ * M3_) + (N3_ * N3_))) -
             atan((N3_ / M3_)) * 57296 / 1000;

    */
    double l1 = vec3Sum1_[0] * vec3Sum1_[0] + vec3Sum1_[1] * vec3Sum1_[1] + vec3Sum1_[2] * vec3Sum1_[2];
    double i1 = (14699.02 - l1) / 13858.6;
     alfa1_ = acos(i1) * 57296 / 1000;
    double l2 = vec3Sum2_[0] * vec3Sum2_[0] + vec3Sum2_[1] * vec3Sum2_[1] + vec3Sum2_[2] * vec3Sum2_[2];
    double i2 = (14699.02 - l2) / 13858.6;
     alfa2_ = acos(i2) * 57296 / 1000;
    double l3 = vec3Sum3_[0] * vec3Sum3_[0] + vec3Sum3_[1] * vec3Sum3_[1] + vec3Sum3_[2] * vec3Sum3_[2];
    double i3 = (14699.02 - l3) / 13858.6;
     alfa3_ = acos(i3) * 57296 / 1000;

    /*   liFrontMag_ = sqrt((vecSum1_[0] * vecSum1_[0]) + (vecSum1_[1] *
vecSum1_[1]) +
                 (vecSum1_[2] * vecSum1_[2]));
liLeftMag_ = sqrt((vecSum2_[0] * vecSum2_[0]) + (vecSum2_[1] * vecSum2_[1]) +
                (vecSum2_[2] * vecSum2_[2]));
liRightMag_ = sqrt((vecSum3_[0] * vecSum3_[0]) + (vecSum3_[1] * vecSum3_[1]) +
                 (vecSum3_[2] * vecSum3_[2]));
e1_ = 57.2958 * cos(((liFrontMag_ * liFrontMag_) + (armLength_ * armLength_) -
                   (pistonLength_ * pistonLength_)) /
                  (2 * armLength_ * liFrontMag_));
e2_ = 57.2958 * cos(((liLeftMag_ * liLeftMag_) + (armLength_ * armLength_) -
                   (pistonLength_ * pistonLength_)) /
                  (2 * armLength_ * liLeftMag_));
e3_ = 57.2958 * cos(((liRightMag_ * liRightMag_) + (armLength_ * armLength_) -
                   (pistonLength_ * pistonLength_)) /
                  (2 * armLength_ * liRightMag_));

*/

    // Serial.print("Front servo angle: ");
    // Serial.println(e1_);
    // Serial.print("Left servo angle: ");
    // Serial.println(e2_);
    // Serial.print("Right servo angle: ");
    // Serial.println(e3_);
    servoAngles_[0] =  alfa1_ - 45;
    servoAngles_[1] =  alfa2_ - 65;
    servoAngles_[2] =  alfa3_ - 45;
    Serial.print("Angle 1: ");
    Serial.println(l3);
    Serial.print("Angle 2: ");
    Serial.println(i3);
    Serial.print("Angle 3: ");
    Serial.println(alfa3_);
}

// Repositions the servos to a predefined angle
void platform::updateServos()
{
    moveTo(1, servoAngles_[0]);
    moveTo(2, servoAngles_[1]);
    moveTo(3, servoAngles_[2]);
}
