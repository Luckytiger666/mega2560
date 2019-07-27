#include "Move.h"
#include "PID.h"


Move moc;
volatile uint32_t Encoder_pluse1 = 0, Encoder_pluse2 = 0, Encoder_pluse3 = 0, Encoder_pluse4 = 0;
void Encoder1_Code(){Encoder_pluse1++;};
void Encoder2_Code(){Encoder_pluse2++;};
void Encoder3_Code(){Encoder_pluse3++;};
void Encoder4_Code(){Encoder_pluse4++;};
void Run_1(){moc.StraightOn_1(5.0);};


void setup()
{
  Serial.begin(9600);
  //attachInterrupt(digitalPinToInterrupt(2), Encoder1_Code, CHANGE);
  moc.init(Encoder1_Code, Encoder2_Code, Encoder3_Code, Encoder4_Code);
  moc.Go();
}


void loop()
{
  // moc.StraightOn(3.0);
  // moc.StraightOn(1.0);
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
