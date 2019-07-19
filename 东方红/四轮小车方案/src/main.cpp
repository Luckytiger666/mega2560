#include "Motor.h"
#include "PID.h"
// #include <Servo.h>

//Define Variables we'll be connecting to
float Setpoint, Input, Output;
volatile uint32_t Encoder_pluse1, Encoder_pluse2, Encoder_pluse3, Encoder_pluse4;
//Specify the links and initial tuning parameters
float Kp = 25.04, Ki = 255.00, Kd = 0.01;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);
Encoder_Motor myMotor(1, 2, 0);
void Encoder1_Code(){Encoder_pluse1++;};


void setup()
{
  Serial.begin(9600);
  myMotor.SetSpeed(100);
  //Motor.Get_Rad();
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  //attachInterrupt(digitalPinToInterrupt(2), Encoder1_Code, CHANGE);
  myMotor.init(Encoder1_Code);
}


void loop()
{
  unsigned int i = 0;
  myMotor.Run(FORWORD);
  while(i < 50){
    Setpoint = 3.0;
    delay(50);
    Input = myMotor.GetRad(Encoder_pluse1);
    myPID.Compute();
    myMotor.SetSpeed(Output);
    // Serial.println(Input);
    i++;
  }
  i = 0;
  while(i < 50){
    Setpoint = 3.0;
    delay(50);
    Input = myMotor.GetRad(Encoder_pluse1);
    myPID.Compute();
    myMotor.SetSpeed(Output);
    // Serial.println(Input);
    i++;
  }
}
