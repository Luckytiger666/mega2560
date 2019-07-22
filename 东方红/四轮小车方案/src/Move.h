#ifndef _MOVE__H
#define _MOVE__H


#include "Motor.h"
#include "Sensor.h"
#include "Wire.h"
#include "PID.h"
#include "math.h"


// TODO:为了方便调试前两个电机的引脚定义在Motor.h中
// TODO:引脚定义每辆车不同，在这定义
#define MOTOR_3_IN1 1
#define MOTOR_3_IN2 2
#define MOTOR_3_PWM_PIN 3
#define MOTOR_3_AM 4
#define MOTOR_4_IN1 5
#define MOTOR_4_IN2 6
#define MOTOR_4_PWM_PIN 7
#define MOTOR_4_AM 8
#define FRONT_ULT_ECHO 9
#define FRONT_ULT_TRIG 10
#define LEFT_FRONT_ULT_ECHO A0
#define LEFT_FRONT_ULT_TRIG A1
#define LEFT_BACK_ULT_ECHO 13
#define LEFT_BACK_ULT_FRIG 14
#define COUNTER_ULT_ECHO 15
#define COUNTER_ULT_FRIG 16


const float speed_pid_P = 16.00, speed_pid_I = 140.00, speed_pid_D = 0.001;
const float angle_pid_P = 16.00, angle_pid_I = 0.00, angle_pid_D = 0.00;
const float position_pid_P = 16.00, position_pid_I = 0.00, position_pid_D = 0.00;
extern volatile uint32_t Encoder_pluse1, Encoder_pluse2, Encoder_pluse3, Encoder_pluse4;


class Move
{
private:
    Encoder_Motor motor1_;
    Encoder_Motor motor2_;
    Encoder_Motor motor3_;
    Encoder_Motor motor4_;
    Ult front_ult_;
    Ult left_front_ult_;
    Ult left_back_ult_;
    Ult counter_ult_;
    PID speed_pid_;
    PID angle_pid_;
    PID position_pid_;
    float speed_pid_input_, speed_pid_output_, speed_pid_setpoint_;
    float angle_pid_input_, angle_pid_output_, angle_pid_setpoint_;
    float position_pid_input_, position_pid_output_, position_pid_setpoint_;
    float left_distance_,right_distance_;
    float right_PWM_, left_PWM_;
    float angle;
    void Mow();
    void Left_90();
    void Right_90();
    void Judge();
public:
    Move();
    void init(FuncPtr encoder1, FuncPtr encoder2, FuncPtr encoder3, FuncPtr encoder4);
    void Gogogo();
    void StraightOn(float speed);
    // ~Move();
};


#endif //!_MOVE__H