#ifndef _MOVE__H
#define _MOVE__H


#include "Motor.h"
#include "Sensor.h"
#include "Wire.h"
#include "PID.h"
#include "math.h"
#include "FlexiTimer2.h"


// TODO:为了方便调试前两个电机的引脚定义在Motor.h中
// TODO:引脚定义每辆车不同，在这定义
#define MOTOR_3_IN1 11
#define MOTOR_3_IN2 12
#define MOTOR_3_PWM_PIN 13
#define MOTOR_3_AM 19
#define MOTOR_4_IN1 10
#define MOTOR_4_IN2 9
#define MOTOR_4_PWM_PIN 8
#define MOTOR_4_AM 18
#define FRONT_ULT_ECHO A8
#define FRONT_ULT_TRIG A9
#define LEFT_FRONT_ULT_ECHO A8
#define LEFT_FRONT_ULT_TRIG A9
#define LEFT_BACK_ULT_ECHO A10
#define LEFT_BACK_ULT_TRIG A11
#define COUNTER_ULT_ECHO 0
#define COUNTER_ULT_TRIG 0
#define WIFI_TX_PIN 0
#define WIFI_RX_PIN 0


const float speed_pid_P = 16.00, speed_pid_I = 140.00, speed_pid_D = 0.05;
const float angle_pid_P = 140.00, angle_pid_I = 1.0, angle_pid_D = 0.05;
const float position_pid_P = 16.00, position_pid_I = 0.00, position_pid_D = 0.00;
extern volatile uint32_t Encoder_pluse1, Encoder_pluse2, Encoder_pluse3, Encoder_pluse4;
extern void Run_1();


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
    FuncPtr MoveFunc;
    float speed_pid_input_, speed_pid_output_, speed_pid_setpoint_;
    float angle_pid_input_, angle_pid_output_, angle_pid_setpoint_;
    float position_pid_input_, position_pid_output_, position_pid_setpoint_;
    float left_front_distance_, left_back_distance_;
    float right_PWM_, left_PWM_;
    float angle;
    uint16_t speed_array_[3];
public:
    Move();
    void init(FuncPtr encoder1, FuncPtr encoder2, FuncPtr encoder3, FuncPtr encoder4);
    void Go(); //本次比赛主要运行在此函数中
    void Mow();
    void Left_90();
    void Right_90();
    void Judge();
    void SetSpeed();
    void StraightOn_1(float speed); //刚开始比赛时的一段直行
    // ~Move();
};


#endif //!_MOVE__H
