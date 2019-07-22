/**********************************************************************
*File:Sensor.cpp
*Copyright:张博闻产业有限公司
*Author:最帅的张博闻
*Date:2019-07-17
*Description:各种常用传感器的使用
*更改历史:
*---------------------------------------------------------------------*												       
*  <Date>     | <Version> | 	<Author>    | <Description>           *
*-------------------------------------------------------------------- *
*  2019/07/17 |   1.0.0   |	  	 张博闻	     | Create file             *
*---------------------------------------------------------------------*
*                                                                     *
***********************************************************************/


#include "Sensor.h"


/**
 * 说明：超声波的构造函数
 * 参数：echo引脚号， trig引脚号
 * 返回值：无
 * 作者：最帅的张博闻
 * Copyright:张博闻产业有限公司
 */
Ult::Ult(int echo, int trig) {
	Echo = echo;
	Trig = trig;
	//定义引脚模式
	pinMode(Trig, OUTPUT);
	pinMode(Echo, INPUT);
}


/**
 * 说明：超声波测距函数
 * 参数：无
 * 返回值：测得的距离
 * 作者：最帅的张博闻
 * Copyright：张博闻产业有限公司
 */
float Ult::Range() {
	float distance;
	digitalWrite(Trig, LOW);
	delayMicroseconds(2);
	digitalWrite(Trig, HIGH);
	delayMicroseconds(10);
	digitalWrite(Trig, LOW);
	distance = pulseIn(Echo, HIGH) / 58.00;
	Serial.println(distance);
	return distance;
}


/**
 * 说明：红外传感器， 色标传感器的构造函数
 * 参数：红外引脚号
 * 返回值： 无
 * 作者：最傻的吴宏达（张博闻将整个类重写了一遍，他表示不认可这个第一作者）
 * Copyright：张博闻产业有限公司
 */
Infr::Infr(int pin) {
	outputPin = pin;
	pinMode(outputPin, INPUT);
}


/**
 * 说明：获取红外，色标的值
 * 参数：无
 * 返回值： 无
 * 作者：最傻的吴宏达（张博闻将整个类重写了一遍，他表示不认可这个第一作者）
 * FIXME:吴宏达你告诉我，我一行代码完成的工作，你为啥用了四行
 * Copyright：张博闻产业有限公司
 */
bool Infr::GetValue() {
	return digitalRead(outputPin);
}
