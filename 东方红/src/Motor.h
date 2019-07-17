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
    int IN1,IN2,PWM_PIN;
public:
    friend class Move;
    Motor(int no);
    Motor(int in1, int in2, int pwm_pin);
    void SetSpeed(int speed);
    void Run(bool direction);
    //~Motor();
};


class Encoder_Motor:public Motor{
private:
  int AM,BM;
  unsigned int old_time = 0;
  unsigned int new_time;
  unsigned int times; //时间变量
  float n; // 用来存储转速的变量
//   FuncPtr func = NULL;
public:
  Encoder_Motor(int no, int am, int bm = 0);
  Encoder_Motor(int in1, int in2, int pwm_pin, int am, int bm = 0);
  void init(FuncPtr Encoder_func);
  float Get_Rad(volatile int &count);//获取转速
};





#endif //!_MOVE__H
