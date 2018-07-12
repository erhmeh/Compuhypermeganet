#include <Arduino.h>
#include <quadruped.h>
#include <Servo.h>

void quadruped::setPins(int pins[]) {
    for(int i=0;i<7;i++) {
        pins_[i] = pins[i];
    }
}

void quadruped::attachServos() {
    for(int i=0;i<7;i++) {
        servos[i].attach(pins_[i]);
    }
}

void quadruped::standUp() {

}

void quadruped::lowerDown() {

}

void quadruped::moveForward(int steps) {

}

void quadruped::moveBackward(int steps) {

}