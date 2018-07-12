#include "platform.h"

// Attaches pins. Parse a int[3] with the pin numbers in the order of 1 -> front, 2 -> left, 3 -> right
void platform::attachServos(int *pins)
{
    frontServo_.attach(pins[0]);
    leftServo_.attach(pins[1]);
    rightServo_.attach(pins[2]);
}

// Moves a servo to a specified angle 1 -> front, 2 -> left, 3 -> right
void platform::moveTo(int servo, int angle){

}