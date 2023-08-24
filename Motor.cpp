#include"Motor.h"
#define MAX 100

int PWM1 = 6;
int IN1 = 10;
int IN2 = 11;

int PWM2 = 3;
int IN3 = 12;
int IN4 = 13;


float err =0,Ierr=0,derr=0;
float Kp1= 400,Ki1 = 100/18,Kd1 = 150;
float Kp2=400,Ki2 = 100/18,Kd2 = 150;
float goal =0.0f;
int pwm;



void Motor1_setup()
{
  Serial.begin(9600);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(PWM1,OUTPUT);
  // pinMode(ENC_A,INPUT);
  // pinMode(ENC_B,INPUT);
  // attachInterrupt(0,Code0,FALLING);
  // attachInterrupt(0,Code0,CHANGE);
  // attachInterrupt(1,Code1,CHANGE);//计数用到的代码，之后可能会用到
  //Timer1.initialize(50000);
  //Timer1.attachInterrupt(TimerIsr);
}


int PID1(float goal,float now)
{
  derr=goal-now-err;
  err=goal-now;
  Ierr+=err;
  float PWM=Ki1*(Ierr)+Kp1*(err)+Kd1*(derr);
  return PWM;
}

void Balance1(int fLastRoll)
{
    pwm=PID1(goal,fLastRoll);
    if(abs(pwm)>MAX&&abs(pwm)<255) //用于防止pwm超过0-255范围，可以去掉
    {
        if(pwm<0){pwm = -MAX;}
        else{pwm = MAX;}
    }
    // if(abs(pwm)>=255)
    // {
    //   analogWrite(PWM1,0);
    // }
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
    analogWrite(PWM1,pwm);
    // Serial.print(" goal:");
    // Serial.print(goal);
    // Serial.print(" rpm:");
    // Serial.println(rpm);
}





void Motor2_setup()
{
  Serial.begin(9600);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(PWM2,OUTPUT);
  // pinMode(ENC_A,INPUT);
  // pinMode(ENC_B,INPUT);
  //attachInterrupt(0,Code0,FALLING);
  // attachInterrupt(0,Code0,CHANGE);//计数用到的代码，之后可能会用到
  // attachInterrupt(1,Code1,CHANGE);
  //Timer1.initialize(50000);
  //Timer1.attachInterrupt(TimerIsr);
}


int PID2(float goal,float now)
{
  derr=goal-now-err;
  err=goal-now;
  Ierr+=err;
  float PWM=Ki2*(Ierr)+Kp2*(err)+Kd2*(derr);
  return PWM;
}

void Balance2(int fLastPitch)
{
    pwm=PID2(goal,fLastPitch);
    if(abs(pwm)>MAX) //用于防止pwm超过0-255范围，可以去掉
    {
        if(pwm<0){pwm = -MAX;}
        else{pwm = MAX;}
    }
    if(pwm <0) //用于处理目标转速为负数时情况
    {
        digitalWrite(IN3,LOW); //反转
        digitalWrite(IN4,HIGH);
        pwm = -pwm;
    }
    else
    {
        digitalWrite(IN3,HIGH); //正转
        digitalWrite(IN4,LOW);
    }
    analogWrite(PWM2,pwm);
    // Serial.print(" goal:");
    // Serial.print(goal);
    // Serial.print(" rpm:");
    // Serial.println(rpm);
}





// void Code0()
// {
//     if(digitalRead(ENC_A)  == LOW) //判断A为下降沿
//     {
//       if(digitalRead(ENC_B) == LOW)//正转
//       {
//        count += 1;
//       }
//       if(digitalRead(ENC_B) == HIGH)//反转
//       {
//         count -= 1;
//       }
//     }
//     else  
//     {
//       if(digitalRead(ENC_B) == LOW)//正转
//       {
//         count -= 1;        
//       }
//       if(digitalRead(ENC_B) == HIGH)//反转
//       {
//         count += 1;
//       }
//     }
// }
// void Code1()
// {
//     if(digitalRead(ENC_B)  == LOW) //判断B为下降沿
//     {
//       if(digitalRead(ENC_A) == HIGH)//正转
//       {
//        count += 1;
//       }
//       if(digitalRead(ENC_A) == LOW)//反转
//       {
//         count -= 1;
//       }
//     }
//     else  
//     {
//       if(digitalRead(ENC_A) == HIGH)//正转
//       {
//         count -= 1;        
//       }
//       if(digitalRead(ENC_A) == LOW)//反转
//       {
//         count += 1;
//       }
//     }
// }