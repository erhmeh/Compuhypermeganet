#include <Arduino.h>
#include <quadruped.h>
#include <Servo.h>

#define HIP_SERVO 0
#define TIB_FEM_SERVO 1
#define SERVO_DELAY 20
#define HIP_ANGLE_OFFSET 0
#define JOINT_ANGLE_OFFSET 0

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
    /* set coordinates */
    double x_0 = femur_ + coxa_/(sq(2)), y_0 = femur_ + coxa_/(sq(2)), z_0 = 0;
    double z_off = tibia_ - femur_/(sq(2));
    position_t target_coodinate = {x_0, y_0, z_0};
    /* calculate required angles */
    double gamma = calculateAngle(target_coodinate, HIP_SERVO, z_off);
    double alpha = calculateAngle(target_coodinate, TIB_FEM_SERVO, z_off);
    for(int i = 0; i<7; i++)
    {
        if(!i || i%2==0) /* even numbered (hip servos) */
        {
            writeServos(gamma);
        } else { /* odd numbered (tib-fem servos) */
            writeServos(alpha);
        }
    }
}

/* Lower down from standing position */
void quadruped::lowerDown()
{
    /* set coordinates */
    double x_0 = femur_/sqrt(2) + sqrt(2*pow(femur_,2)-4*(femur_-tibia_))/2;
    double y_0 = femur_/sqrt(2) + sqrt(2*pow(femur_,2)-4*(femur_-tibia_))/2;
    double z_0 = 0;
    double z_off = tibia_ - femur_/(sq(2));
    position_t target_coodinate = {x_0, y_0, z_0};
    /* calculate required angles */
    double gamma = calculateAngle(target_coodinate, HIP_SERVO, z_off) + HIP_ANGLE_OFFSET;
    double alpha = calculateAngle(target_coodinate, TIB_FEM_SERVO, z_off) + JOINT_ANGLE_OFFSET;
    for(int i = 0; i<7; i++)
    {
        if(!i || i%2==0) /* even numbered (hip servos) */
        {
            writeServos(gamma);
            
        } else { /* odd numbered (tib-fem servos) */
            writeServos(alpha);
        }
    }
}

void quadruped::writeServos(double angle, int servo)
{
    if(angles_[servo] < angle) 
    { /* check if we need to decrement to or increase to angle */
        for(int j = angles_[servo]; j<=angle; j++) 
        {
            servos_[servo].write(j);
            delay(SERVO_DELAY);
        }
    } else if(angles_[servo] > angle) {
        for(int k = angles[i]; k>=angle; k--) 
        {
            servos_[servo].write(k);
            delay(SERVO_DELAY);
        }
    }
    angles_[i] = angle;
}

/* Move forward by specified number of steps */
void quadruped::moveForward(int steps)
{
}

/* Move backward by specified number of steps */
void quadruped::moveBackward(int steps)
{
}

/* Calculates servo angles based on given leg coordinates using inverse kinematics */
double quadruped::calculateAngle(position_t effector_target_coordinate, int servo_type, double z_off)
{
    double angle, phi_3, r_3, r_2, r_1;
    if(servo_type)
    {
        /* tib-fem servo */
        r_1 = z_off - effector_target_coordinate.z;
        r_2 = sq(pow(effector_target_coordinate.x,2)+pow(effector_target_coordinate.y,2));
        r_3 = sq(pow(r_1,2)+pow(r_2,2));
        phi_3 = acos((pow(r_3,2) - pow(tibia_,2) - pow(femur_,2))/(-2*tibia_*femur_));
        angle = 180-phi_3;
    } else {
        /* hip servo */
        angle = atan(effector_target_coordinate.x/effector_target_coordinate.y);
    }
    return angle;
}