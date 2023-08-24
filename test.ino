#include "Wire.h"
#include "Math.h"
#include"Motor.h"
#include"mpu6050.h"
#include"connect_to_rocker.h"

data Data(0.0f,0.0f,0.0f,0.0f,0.0f,0);//用于储存mpu6050中的数据

void setup() {
  Serial.begin(9600); //初始化串口，指定波特率
  Wire.begin(); //初始化Wire库
  WriteMPUReg(0x6B, 0); //启动MPU6050设备
  Motor1_setup();//启动下方的电机
  Motor2_setup();//启动上方的电机
}

void loop() {
  Data=getdata(Data);//从mpu6050中获取数据存放到Data中
  BTdata btdata=getBTdata();
  if(btdata!=NULLBTDATA)
  {

  }

  Balance1(Data.Pitch);
  Balance2(-Data.Pitch);

  //  Serial.print("Roll:");
  //  Serial.print(Data.Roll); Serial.print('(');
  //  Serial.print(Data.Roll_w); Serial.print("),\tPitch:");
  //  Serial.print(Data.Pitch); Serial.print('(');
  //  Serial.print(Data.Pitch_w); Serial.print(")\n");
  //  Serial.print(Data.temperature); Serial.print("\n");
  delay(5);
}
