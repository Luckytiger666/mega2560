/**********************************************************************
*File:Move.cpp
*Copyright:张博闻产业有限公司
*Author:最帅的张博闻
*Date:2019-07-17
*Description:本次比赛四轮车方案
*更改历史:
*-------------------------------------------------------------------------*												       
*  <Date>     | <Version> | 	<Author>    |     <Description>           *
*-------------------------------------------------------------------------*
*  2019/07/19 |   1.0.0   | 	  张博闻     |      Create file            *
*-------------------------------------------------------------------------*
***************************************************************************/


#include "Move.h"


Move::Move(): motor1_(MOTOR_1_IN1, MOTOR_1_IN2, MOTOR_1_PWM_PIN, MOTOR_1_AM) , motor2_(MOTOR_2_IN1, MOTOR_2_IN2, MOTOR_2_PWM_PIN, MOTOR_2_AM)
            , motor3_(MOTOR_3_IN1, MOTOR_3_IN2, MOTOR_3_PWM_PIN, MOTOR_3_AM) , motor4_(MOTOR_4_IN1, MOTOR_4_IN2, MOTOR_4_PWM_PIN, MOTOR_4_AM)
            , front_ult_(FRONT_ULT_ECHO, FRONT_ULT_TRIG)                     , left_front_ult_(LEFT_FRONT_ULT_ECHO, LEFT_FRONT_ULT_TRIG)
            , left_back_ult_(LEFT_BACK_ULT_ECHO, LEFT_BACK_ULT_TRIG)         , counter_ult_(COUNTER_ULT_ECHO, COUNTER_ULT_TRIG)
            , speed_pid_(&speed_pid_input_, &speed_pid_output_, &speed_pid_setpoint_, speed_pid_P, speed_pid_I, speed_pid_D, DIRECT)
            , angle_pid_(&angle_pid_input_, &angle_pid_output_, &angle_pid_setpoint_, angle_pid_P, angle_pid_I, angle_pid_D, DIRECT)
            , position_pid_(&position_pid_input_, &position_pid_output_, &position_pid_setpoint_, position_pid_P, position_pid_I, position_pid_D, DIRECT)
        {
            speed_pid_.SetMode(AUTOMATIC);
            angle_pid_.SetMode(AUTOMATIC);
            position_pid_.SetMode(AUTOMATIC);
            position_pid_setpoint_ = 10;
            angle_pid_setpoint_ = 0;
            left_distance_ = right_distance_ = 0;
            angle = 0;
        }


void Move::init(FuncPtr encoder1, FuncPtr encoder2, FuncPtr encoder3, FuncPtr encoder4, FuncPtr Runtime){
    motor1_.init(encoder1);
    // motor2_.init(encoder2);
    // motor3_.init(encoder3);
    // motor4_.init(encoder4);
    FlexiTimer2::set(50, Runtime);
    FlexiTimer2::start();
}


void Move::StraightOn(float speed){
    //速度PID调试
    speed_pid_setpoint_ = speed;
    speed_pid_input_ = motor1_.GetRad(Encoder_pluse1);
    speed_pid_.Compute();
    motor1_.Run(1);
    motor1_.SetSpeed(speed_pid_output_);
    Serial.println(speed_pid_input_);
    // motor2_.SetSpeed(speed_pid_output_);
    // speed_pid_input_ = motor2_.GetRad(Encoder_pluse1);
    // left_PWM_ = speed_pid_output_;
    // speed_pid_.Compute();
    // motor3_.SetSpeed(speed_pid_output_);
    // motor4_.SetSpeed(speed_pid_output_);
    // right_PWM_ = speed_pid_output_;
    //角度PID调试
    // angle_pid_input_ = atan2(left_front_ult_.Range(), 10);
    // angle_pid_.Compute();
    // motor1_.SetSpeed(left_PWM_ + angle_pid_output_);
    // motor2_.SetSpeed(left_PWM_ + angle_pid_output_);
    // motor3_.SetSpeed(right_PWM_ - angle_pid_output_);
    // motor4_.SetSpeed(right_PWM_ - angle_pid_output_);
    // //距离PID调试
    // position_pid_input_ = (left_front_ult_.Range() + left_back_ult_.Range())/2;
    // position_pid_.Compute();
    // motor1_.SetSpeed(left_PWM_ + position_pid_output_);
    // motor2_.SetSpeed(left_PWM_ + position_pid_output_);
    // motor3_.SetSpeed(right_PWM_ - position_pid_output_);
    // motor4_.SetSpeed(right_PWM_ - position_pid_output_);
}
