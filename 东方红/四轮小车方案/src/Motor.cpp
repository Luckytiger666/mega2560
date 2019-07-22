/**********************************************************************
*File:Motor.cpp
*Copyright:张博闻产业有限公司
*Author:最帅的张博闻
*Date:2019-07-17
*Description:包含电机与编码电机的控制与使用
*更改历史:
*-------------------------------------------------------------------------*												       
*  <Date>     | <Version> | 	<Author>    |     <Description>           *
*-------------------------------------------------------------------------*
*  2019/07/17 |   1.0.0   | 	  张博闻     |      Create file            *
*-------------------------------------------------------------------------*
*  2019/07/18 |   1.0.0   | 	  张博闻     |  完善了测速算法，优化了存储空间  *             
*-------------------------------------------------------------------------*
*                                                                         *
***************************************************************************/


#include "Motor.h"


/***************************************************
*说明：Motor的构造函数, 使用预制电机
*参数：电机号
*返回值：无
*注释：电机引脚号定义在Motor.h文件中
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Motor::Motor(uint8_t no){
	//预设电机
    if (no == 1){
        in1_ = MOTOR_1_IN1;
        in2_ = MOTOR_1_IN2;
        pwm_pin_ = MOTOR_1_PWM_PIN;
    }
    else if (no == 2){
        in1_ = MOTOR_2_IN1;
        in2_ = MOTOR_2_IN2;
        pwm_pin_ = MOTOR_2_PWM_PIN;
    }
	//定义引脚
	pinMode(STBY, OUTPUT);
	pinMode(pwm_pin_, OUTPUT);
	pinMode(in1_, OUTPUT);
	pinMode(in2_, OUTPUT);
}


/***************************************************
*说明：Motor的构造函数, 自定义引脚
*参数：in1， in2 ，PWM引脚
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Motor::Motor(uint8_t in1, uint8_t in2, uint8_t pwm_pin){
	//自己构造电机
    in1_ = in1;
    in2_ = in2;
    pwm_pin_ = pwm_pin;
	//定义引脚
	pinMode(STBY, OUTPUT);
	pinMode(pwm_pin_, OUTPUT);
	pinMode(in1_, OUTPUT);
	pinMode(in2_, OUTPUT);
}


/***************************************************
*说明：设定电机转速
*参数：PWM波(0~255)
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
void Motor::SetSpeed(uint8_t speed){
    analogWrite(pwm_pin_, speed);
}


/***************************************************
*说明：让电机转动，应该先调用SetSpeed函数
*参数：FORWORD或BACKWORD
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
void Motor::Run(bool direction){
    if (direction == FORWORD){
      	digitalWrite(STBY, HIGH);
        digitalWrite(in1_, HIGH);
        digitalWrite(in2_, LOW);
    }
    else if (direction == BACKWORD){
      	digitalWrite(STBY, HIGH);
        digitalWrite(in1_, LOW);
        digitalWrite(in2_, HIGH);
    }
}


/***************************************************
*说明：编码电机的构造函数，使用预设电机
*参数：预设电机号， AM相引脚, BM相引脚
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Encoder_Motor::Encoder_Motor(uint8_t no, uint8_t am):Motor(no){
	AM = am;
	pinMode(AM, INPUT);
}


/***************************************************
*说明：编码电机的构造函数, 自定义电机引脚
*参数：in1, in2 , PWM引脚， AM相引脚， BM相引脚
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Encoder_Motor::Encoder_Motor(uint8_t in1, uint8_t in2, uint8_t pwm_pin, uint8_t am):Motor(in1, in2, pwm_pin){
	AM = am;
	pinMode(AM, INPUT);
	//attachPinChangeInterrupt(digitalPinToInterrupt(2), *(FuncPtr)(&Encoder_Motor::Code), CHANGE);
}


/***************************************************
*说明：用来初始化计数程序, 注意中断引脚默认用AM，想改成BM
*	  的话，过来改！！！
*参数：外部定义的初始化函数（静态函数)
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
void Encoder_Motor::init(FuncPtr Encoder_func){
	attachInterrupt(digitalPinToInterrupt(AM), Encoder_func, CHANGE);
}


/***************************************************
*说明：获取当前电机转速
*参数：电机脉冲数
*返回值：电机转速
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
float Encoder_Motor::GetRad(volatile uint32_t &count){
	count = 0;
	// new_time = millis();
	// times = new_time - old_time;
	// // Serial.println(count);
	delay(100);
	n = count*10.00/520.00;
	count = 0;
	old_time = millis();
	// Serial.println(n);
	return n;
}
