#include "Motor.h"
#include "PID.h"
//#include "PinChangeInt.h"


//Define Variables we'll be connecting to
float Setpoint, Input, Output;
volatile int Encoder_pluse1, Encoder_pluse2, Encoder_pluse3, Encoder_pluse4;
//Specify the links and initial tuning parameters
float Kp = 16, Ki = 255, Kd = 0.0011;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
Encoder_Motor myMotor(1, 2, 0);
void Encoder1_Code();

void setup()
{
  Serial.begin(9600);
  myMotor.SetSpeed(0);
  //Motor.Get_Rad();
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  //attachInterrupt(digitalPinToInterrupt(2), Encoder1_Code, CHANGE);
  myMotor.init(Encoder1_Code);
}


void loop()
{
  unsigned long i = 0;
  myMotor.Run(FORWORD);
  while(i < 500){
    Setpoint = 1.0;
    Input = myMotor.Get_Rad(Encoder_pluse1);
    myPID.Compute();
    myMotor.SetSpeed(Output);
    Serial.println(Input);
    i++;
  }
  i = 0;
  while(i < 500){
    Setpoint = 2.0;
    Input = myMotor.Get_Rad(Encoder_pluse1);
    myPID.Compute();
    myMotor.SetSpeed(Output);
    Serial.println(Input);
    i++;
  }
}


/**
 * 说明：电机1的编码计数
 * 参数：无
 */
void Encoder1_Code(){
	Encoder_pluse1++;
 	// Serial.print("count:");
	// Serial.println(Encoder_pluse1);
}