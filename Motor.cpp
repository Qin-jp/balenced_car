#include"Motor.h"
//#include"Wire.h"
//#include"Arduino.h"

int ENC_A =2; //电机的编码器A端
int ENC_B =3; //电机的编码器B端
int count =0; //上升沿（脉冲）数量
int PWM = 6;
int IN1 = 10;
int IN2 = 11;

float err =0,Ierr=0,derr=0;
float Kp= 10,Ki = 0,Kd = 0;

float rpm;
float goal =0;
int pwm;

// float fLastRoll = 0.0f; //上一次滤波得到的Roll角
// float fLastPitch = 0.0f; //上一次滤波得到的Pitch角


void Motor_setup()
{
  Serial.begin(9600);
    pinMode(IN1,OUTPUT);
    pinMode(IN2,OUTPUT);
    pinMode(PWM,OUTPUT);
    pinMode(ENC_A,INPUT);
    pinMode(ENC_B,INPUT);
    //attachInterrupt(0,Code0,FALLING);//自己写一个四倍频算法
    attachInterrupt(0,Code0,CHANGE);
    attachInterrupt(1,Code1,CHANGE);
    //Timer1.initialize(50000);
    //Timer1.attachInterrupt(TimerIsr);
}


int PID(float goal,float now)
{
  derr=goal-now-err;
  err=goal-now;
  Ierr+=err;
  float PWM=Ki*(Ierr)+Kp*(err)+Kd*(derr);
  return PWM;
}

void TimerIsr(int fLastRoll)
{
    rpm = count*60.0/13.0/4.0;

    count =0;
    pwm=PID(goal,fLastRoll);
    if(abs(pwm)>100) //用于防止pwm超过0-255范围，可以去掉
    {
        if(pwm<0){pwm = -100;}
        else{pwm = 100;}
    }
    if(pwm <0) //用于处理目标转速为负数时情况
    {
        digitalWrite(IN1,LOW); //反转
        digitalWrite(IN2,HIGH);
        pwm = -pwm;
    }
    else
    {
        digitalWrite(IN1,HIGH); //正转
        digitalWrite(IN2,LOW);
    }
    analogWrite(PWM,pwm);
    Serial.print(" goal:");
    Serial.print(goal);
    Serial.print(" rpm:");
    Serial.println(rpm);
}







void Code0()
{
    if(digitalRead(ENC_A)  == LOW) //判断A为下降沿
    {
      if(digitalRead(ENC_B) == LOW)//正转
      {
       count += 1;
      }
      if(digitalRead(ENC_B) == HIGH)//反转
      {
        count -= 1;
      }
    }
    else  
    {
      if(digitalRead(ENC_B) == LOW)//正转
      {
        count -= 1;        
      }
      if(digitalRead(ENC_B) == HIGH)//反转
      {
        count += 1;
      }
    }
}
void Code1()
{
    if(digitalRead(ENC_B)  == LOW) //判断B为下降沿
    {
      if(digitalRead(ENC_A) == HIGH)//正转
      {
       count += 1;
      }
      if(digitalRead(ENC_A) == LOW)//反转
      {
        count -= 1;
      }
    }
    else  
    {
      if(digitalRead(ENC_A) == HIGH)//正转
      {
        count -= 1;        
      }
      if(digitalRead(ENC_A) == LOW)//反转
      {
        count += 1;
      }
    }
}