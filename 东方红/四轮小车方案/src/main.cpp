#include "Move.h"
#include "PID.h"



//Define Variables we'll be connecting to
float Setpoint, Input, Output;
Move moc;
volatile uint32_t Encoder_pluse1, Encoder_pluse2, Encoder_pluse3, Encoder_pluse4;
//Specify the links and initial tuning parameters
float Kp = 16.00, Ki = 140.00, Kd = 0.001;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
Encoder_Motor myMotor(1, 2);
void Encoder1_Code(){Encoder_pluse1++;};
uint16_t count = 0;
void Run(){moc.StraightOn(3.0);};


void setup()
{
  Serial.begin(9600);
  Serial3.begin(9600);
  myMotor.SetSpeed(100);
  //Motor.Get_Rad();
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  //attachInterrupt(digitalPinToInterrupt(2), Encoder1_Code, CHANGE);
  myMotor.init(Encoder1_Code);
  moc.init(Encoder1_Code, Encoder1_Code, Encoder1_Code, Encoder1_Code, Run);
}


void loop()
{
  // Serial3.println("Hello");
  // Serial.println(123);
  // delay(1000);
  // while(i < 5)0){
  //   Setpoint = 3;
  //   delay(50);
  //   Input = myMotor.GetRad(Encoder_pluse1);
  //   myPID.Compute();
  //   myMotor.SetSpeed(Output);
  //   Serial.println(Output);
  //   delay(40);
  //   i++;
  // }
  // i = 0;
  // myMotor.Run(BACKWORD);
  // while(i < 50){
  //   Setpoint = 3.0;
  //   delay(50);
  //   Input = myMotor.GetRad(Encoder_pluse1);
  //   myPID.Compute();
  //   myMotor.SetSpeed(Output);
  //   Serial.println(Output);
  //   delay(40);
  //   i++;
  // }
}
