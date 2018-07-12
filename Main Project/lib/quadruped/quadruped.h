#ifndef quadruped_H
#define quadruped_H

#include <Arduino.h>
#include <Servo.h>


class quadruped {
    public:
        void setPins(int pin);
        /* Movement functions */
        void standUp();
        void lowerDown();
        void moveForward(int steps);
        void moveBackward(int steps);
    private:
        Servo topLeft_[2];
        Servo topRight_[2];
        Servo bottomLeft_[2];
        Servo bottomRight_[2];
        int pin_;
};

#endif