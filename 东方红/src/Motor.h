#ifndef _MOVE__H
#define _MOVE__H


#include <Arduino.h>
#include <math.h>
//#include "PinChangeInt.h"


#define STBY  10
#define FORWORD 0
#define BACKWORD 1
#define MOTOR_1_IN1 22
#define MOTOR_1_IN2 23
#define MOTOR_1_PWM_PIN 3
#define MOTOR_2_IN1 11
#define MOTOR_2_IN2 12
#define MOTOR_2_PWM_PIN 5


//自定义类型, 用来表示小车的姿态
//Avertence是偏移的意思，曾潇说的就是你，别查词典了，这个是考研高频词
enum Posture{Straight, LeftAvertence, RightAvertence};
typedef void (*FuncPtr)(void);


//电机类
class Motor
{
private:
    uint8_t IN1,IN2,PWM_PIN;
public:
    friend class Move;
    Motor(uint8_t no);
    Motor(uint8_t in1, uint8_t in2, uint8_t pwm_pin);
    void SetSpeed(uint8_t speed);
    void Run(bool direction);
    //~Motor();
};


class Encoder_Motor:public Motor{
private:
  uint8_t AM,BM;
  uint32_t old_time = 0;
  uint32_t new_time;
  uint32_t times; //时间变量
  float n; // 用来存储转速的变量
//   FuncPtr func = NULL;
public:
  Encoder_Motor(uint8_t no, uint8_t am, uint8_t bm = 0);
  Encoder_Motor(uint8_t in1, uint8_t in2, uint8_t pwm_pin, uint8_t am, uint8_t bm = 0);
  void init(FuncPtr Encoder_func);
  float Get_Rad(volatile uint32_t &count);//获取转速
};





#endif //!_MOVE__H
