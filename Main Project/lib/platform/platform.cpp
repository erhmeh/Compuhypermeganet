#include "platform.h"

// Initialises the platform servos, attaches them and then moves them to 90
// degrees
void platform::initPlatform(int *pins)
{
    attachServos(pins);
    for (int i = 1; i <= 3; i++)
    {
        moveTo(i, 45);
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
    matrix[0][0] = cos(pitchR);
    matrix[0][1] = sin(pitchR) * sin(rollR);
    matrix[0][2] = cos(rollR) * sin(rollR);
    matrix[1][0] = 0.0;
    matrix[1][1] = cos(rollR);
    matrix[1][2] = -sin(rollR);
    matrix[2][0] = -sin(pitchR);
    matrix[2][1] = cos(pitchR) * sin(rollR);
    matrix[2][2] = cos(rollR) * cos(pitchR);
    vecSum1_[0] = matrix[0][0] * frontServoVec_[0] +
                  matrix[0][1] * frontServoVec_[1] +
                  matrix[0][2] * frontServoVec_[2];
    vecSum1_[1] = matrix[1][0] * frontServoVec_[0] +
                  matrix[1][1] * frontServoVec_[1] +
                  matrix[1][2] * frontServoVec_[2];
    vecSum1_[2] = matrix[2][0] * frontServoVec_[0] +
                  matrix[2][1] * frontServoVec_[1] +
                  matrix[2][2] * frontServoVec_[2];
    vecSum2_[0] = matrix[0][0] * leftServoVec_[0] +
                  matrix[0][1] * leftServoVec_[1] +
                  matrix[0][2] * leftServoVec_[2];
    vecSum2_[1] = matrix[1][0] * leftServoVec_[0] +
                  matrix[1][1] * leftServoVec_[1] +
                  matrix[1][2] * leftServoVec_[2];
    vecSum2_[2] = matrix[2][0] * leftServoVec_[0] +
                  matrix[2][1] * leftServoVec_[1] +
                  matrix[2][2] * leftServoVec_[2];
    vecSum3_[0] = matrix[0][0] * rightServoVec_[0] +
                  matrix[0][1] * rightServoVec_[1] +
                  matrix[0][2] * rightServoVec_[2];
    vecSum3_[1] = matrix[1][0] * rightServoVec_[0] +
                  matrix[1][1] * rightServoVec_[1] +
                  matrix[1][2] * rightServoVec_[2];
    vecSum3_[2] = matrix[2][0] * rightServoVec_[0] +
                  matrix[2][1] * rightServoVec_[1] +
                  matrix[2][2] * rightServoVec_[2];
    vecSum1_[0] = vecSum1_[0] - frontServoVec_[0];
    vecSum1_[1] = vecSum1_[1] - frontServoVec_[1];
    vecSum1_[2] = vecSum1_[2] - frontServoVec_[2];
    vecSum2_[0] = vecSum2_[0] - leftServoVec_[0];
    vecSum2_[1] = vecSum2_[1] - leftServoVec_[1];
    vecSum2_[2] = vecSum2_[2] - leftServoVec_[2];
    vecSum3_[0] = vecSum3_[0] - rightServoVec_[0];
    vecSum3_[1] = vecSum3_[1] - rightServoVec_[1];
    vecSum3_[2] = vecSum3_[2] - rightServoVec_[2];
    vecSum1_[0] = vecSum1_[0] + platHeight_[0];
    vecSum1_[1] = vecSum1_[1] + platHeight_[1];
    vecSum1_[2] = vecSum1_[2] + platHeight_[2];
    vecSum2_[0] = vecSum2_[0] + platHeight_[0];
    vecSum2_[1] = vecSum2_[1] + platHeight_[1];
    vecSum2_[2] = vecSum2_[2] + platHeight_[2];
    vecSum3_[0] = vecSum3_[0] + platHeight_[0];
    vecSum3_[1] = vecSum3_[1] + platHeight_[1];
    vecSum3_[2] = vecSum3_[2] + platHeight_[2];
    liFrontMag_ = sqrt((vecSum1_[0] * vecSum1_[0]) + (vecSum1_[1] * vecSum1_[1]) +
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
    // Serial.print("Front servo angle: ");
    // Serial.println(e1_);
    // Serial.print("Left servo angle: ");
    // Serial.println(e2_);
    // Serial.print("Right servo angle: ");
    // Serial.println(e3_);
    servoAngles_[0] = e1_;
    servoAngles_[1] = e2_;
    servoAngles_[2] = e3_;
}

// Repositions the servos to a predefined angle
void platform::updateServos()
{
    moveTo(1, servoAngles_[0]);
    moveTo(2, servoAngles_[1]);
    moveTo(3, servoAngles_[2]);
}