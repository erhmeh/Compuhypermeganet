#include <Arduino.h>
#include <quadruped.h>
#include <Servo.h>

/* Assigns pins */
void quadruped::setPins(int pins[])
{
    for (int i = 0; i < 7; i++)
    {
        pins_[i] = pins[i];
    }
}

/* Attaches the servos to the pins */
void quadruped::attachServos()
{
    for (int i = 0; i < 7; i++)
    {
        servos[i].attach(pins_[i]);
    }
}

/* Stand up from resting position */
void quadruped::standUp()
{
}

/* Lower down from standing position */
void quadruped::lowerDown()
{
}

/* Move forward by specified number of steps */
void quadruped::moveForward(int steps)
{
}

/* Move backward by specified number of steps */
void quadruped::moveBackward(int steps)
{
}