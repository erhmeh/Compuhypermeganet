#include "platform.h"

// Initialises the platform servos, attaches them and then moves them to 90 degrees
void platform::initPlatform(int *pins)
{
    attachServos(pins);
    for (int i = 1; i <= 3; i++)
    {
        moveTo(i, 45);
    }
}

// Attaches pins. Parse a int[3] with the pin numbers in the order of 1 -> front, 2 -> left, 3 -> right
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