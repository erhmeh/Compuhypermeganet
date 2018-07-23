#include <Arduino.h>
#include <quadruped.h>
#include <Servo.h>

#define HIP_SERVO 0
#define TIB_FEM_SERVO 1

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

/* Put quadruped in initial position (fully standing) */
void quadruped::startingPosition()
{
    double x_0 = femur_ + coxa_/(sq(2)), y_0 = femur_ + coxa_/(sq(2)), z_0 = 0;
    double z_off = tibia_ - femur_/(sq(2));
    position_t target_coodiante = {x_0, y_0, z_0};
    double gamma = calculateAngle(target_coodiante, HIP_SERVO, z_off);
    double alpha = calculateAngle(target_coodiante, TIB_FEM_SERVO, z_off);
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

double quadruped::calculateAngle(position_t effector_target_coordinate, int servo_type, double z_off)
{
    double angle, phi_3, r_3, r_2, r_1;
    if(servo_type)
    {
        r_1 = z_off - effector_target_coordinate.z;
        r_2 = sq(pow(effector_target_coordinate.x,2)+pow(effector_target_coordinate.y,2));
        r_3 = sq(pow(r_1,2)+pow(r_2,2));
        phi_3 = acos((pow(r_3,2) - pow(tibia_,2) - pow(femur_,2))/(-2*tibia_*femur_));
        angle = 180-phi_3;
    } else {
        angle = atan(effector_target_coordinate.x/effector_target_coordinate.y);
    }
    return angle;
}