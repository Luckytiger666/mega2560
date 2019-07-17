/**********************************************************************
*File:Motor.cpp
*Copyright:张博闻产业有限公司
*Author:最帅的张博闻
*Date:2019-07-17
*Description:包含电机与编码电机的控制与使用
*更改历史:
*---------------------------------------------------------------------*												       
*  <Date>     | <Version> | 	<Author>    | <Description>           *
*-------------------------------------------------------------------- *
*  2019/07/17 |   1.0.0   | 	  张博闻     | Create file             *
*---------------------------------------------------------------------*
*                                                                     *
***********************************************************************/


#include "Motor.h"


/***************************************************
*说明：Motor的构造函数, 使用预制电机
*参数：电机号
*返回值：无
*注释：电机引脚号定义在Motor.h文件中
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Motor::Motor(int no){
	//预设电机
    if (no == 1){
        IN1 = MOTOR_1_IN1;
        IN2 = MOTOR_1_IN2;
        PWM_PIN = MOTOR_1_PWM_PIN;
    }
    else if (no == 2){
        IN1 = MOTOR_2_IN1;
        IN2 = MOTOR_2_IN2;
        PWM_PIN = MOTOR_2_PWM_PIN;
    }
	//定义引脚
	pinMode(STBY, OUTPUT);
	pinMode(PWM_PIN, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
}


/***************************************************
*说明：Motor的构造函数, 自定义引脚
*参数：in1， in2 ，PWM引脚
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Motor::Motor(int in1, int in2, int pwm_pin){
	//自己构造电机
    IN1 = in1;
    IN2 = in2;
    PWM_PIN = pwm_pin;
	//定义引脚
	pinMode(STBY, OUTPUT);
	pinMode(PWM_PIN, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
}


/***************************************************
*说明：设定电机转速
*参数：PWM波(0~255)
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
void Motor::SetSpeed(int speed){
    analogWrite(PWM_PIN, speed);
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
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
    }
    else if (direction == BACKWORD){
      	digitalWrite(STBY, HIGH);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
}


/***************************************************
*说明：编码电机的构造函数，使用预设电机
*参数：预设电机号， AM相引脚, BM相引脚
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Encoder_Motor::Encoder_Motor(int no, int am, int bm):Motor(no){
	AM = am;
	BM = bm;
	pinMode(AM, INPUT);
	pinMode(BM, INPUT);
}


/***************************************************
*说明：编码电机的构造函数, 自定义电机引脚
*参数：in1, in2 , PWM引脚， AM相引脚， BM相引脚
*返回值：无
*作者：最帅的张博闻
*copyright:张博闻产业有限公司
***************************************************/
Encoder_Motor::Encoder_Motor(int in1, int in2, int pwm_pin, int am, int bm):Motor(in1, in2, pwm_pin){
	AM = am;
	BM = bm;
	pinMode(AM, INPUT);
	pinMode(BM, INPUT);
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
float Encoder_Motor::Get_Rad(volatile int &count){
	times = millis();
	if (abs(times - old_time) >= 50)
	{
		// Serial.println(count);
		n = count*20.00/1040.00;
		count = 0;
		old_time = millis();
		// Serial.println(n);
	}
	return n;
}
