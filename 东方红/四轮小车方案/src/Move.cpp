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
            angle_pid_.SetOutputLimits(-255.0F, 255.0F);
            // left_distance_ = right_distance_ = 0;
            angle = 0;
            speed_array_[0] = speed_array_[1] = speed_array_[2] = speed_array_[3] = 0;
        }


void Move::init(FuncPtr encoder1, FuncPtr encoder2, FuncPtr encoder3, FuncPtr encoder4){
    attachInterrupt(digitalPinToInterrupt(MOTOR_1_AM), encoder1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MOTOR_2_AM), encoder2, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MOTOR_3_AM), encoder3, CHANGE);
    attachInterrupt(digitalPinToInterrupt(MOTOR_4_AM), encoder4, CHANGE);
    MoveFunc = Run_1;
    motor1_.Run(FORWORD);
    motor2_.Run(FORWORD);
    motor3_.Run(FORWORD);
    motor4_.Run(FORWORD);
}


void Move::StraightOn_1(float speed){
    //速度PID调试
    speed_pid_setpoint_ = speed;
    left_front_distance_ =  left_front_ult_.Range();
    left_back_distance_ = left_back_ult_.Range();
    speed_pid_input_ = motor1_.GetRad(Encoder_pluse1);
    // Serial.println(speed_pid_input_);
    speed_pid_.Compute();
    speed_array_[0] = speed_pid_output_;
    speed_pid_input_ = motor2_.GetRad(Encoder_pluse2);
    speed_pid_.Compute();
    speed_array_[1] = speed_pid_output_;
    speed_pid_input_ = motor3_.GetRad(Encoder_pluse3);
    // Serial.println(speed_pid_input_);
    speed_pid_.Compute();
    speed_array_[2] = speed_pid_output_;
    // Serial.println(speed_pid_output_)
    speed_pid_input_ = motor4_.GetRad(Encoder_pluse4);
    speed_pid_.Compute();
    speed_array_[3] = speed_pid_output_;
    // 角度PID调试
    angle_pid_setpoint_ = 0;
    angle_pid_input_ = atan2((left_front_distance_ - left_back_distance_), 29.1);
    // Serial.println(angle_pid_input_);
    angle_pid_.Compute();
    // Serial.println(angle_pid_output_);
    speed_array_[0] -= angle_pid_output_;
    speed_array_[1] -= angle_pid_output_;
    speed_array_[2] += angle_pid_output_;
    speed_array_[3] += angle_pid_output_;
    if (left_front_distance_ < 10 && left_back_distance_ < 10){
        speed_array_[2] += 20;
        speed_array_[3] += 20;
    }
     if (left_front_distance_ > 10 && left_back_distance_ > 10){
        speed_array_[0] += 20;
        speed_array_[1] += 20;
    } 
    SetSpeed();
    // //距离PID调试
    // position_pid_input_ = (left_front_ult_.Range() + left_back_ult_.Range())/2;
    // position_pid_.Compute();
    // motor1_.SetSpeed(left_PWM_ + position_pid_output_);
    // motor2_.SetSpeed(left_PWM_ + position_pid_output_);
    // motor3_.SetSpeed(right_PWM_ - position_pid_output_);
    // motor4_.SetSpeed(right_PWM_ - position_pid_output_);
}


void Move::SetSpeed(){
    //限幅
    if (speed_array_[0] > 255)
        speed_array_[0] = 255;
    if (speed_array_[1] > 255)
        speed_array_[1] = 255;
    if (speed_array_[2] > 255)
        speed_array_[2] = 255;
    if (speed_array_[3] > 255)
        speed_array_[3] = 255;
    motor1_.SetSpeed(speed_array_[0] - 15); //FIXME:车身重心不稳
    motor2_.SetSpeed(speed_array_[1] - 15);
    motor3_.SetSpeed(speed_array_[2]);
    motor4_.SetSpeed(speed_array_[3]);
    // analogWrite(8, speed_array_[3]);
    // Serial.println(speed_array_[1]);
    // Serial.println(speed_array_[2]);
    // Serial.println(speed_array_[3]);
}


void Move::Go(){
    motor1_.Run(BACKWORD);
    motor2_.Run(BACKWORD);
    motor3_.Run(FORWORD);
    motor4_.Run(FORWORD);
    //直行时
    FlexiTimer2::set(50, MoveFunc);
    FlexiTimer2::start();
    // while(front_ult_.Range() > 10);
    // FlexiTimer2::stop();
    // Left_90();
    // FlexiTimer2::set(50, MoveFunc);
    // FlexiTimer2::start();
}