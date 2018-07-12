#ifndef quadruped_H
#define quadruped_H

#include <Arduino.h>
#include <Servo.h>


class quadruped {
    public:
        void setPins(int pins[]);
        void attachServos();
        /* Movement functions */
        void standUp();
        void lowerDown();
        void moveForward(int steps);
        void moveBackward(int steps);
    private:
        /* 0-1=top-left, 2-3=top-right, 4-5=bottom-left, 6-7=bottom-right */
        Servo servos[8]; 
        int pins_[8];
};

#endif