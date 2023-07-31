#pragma once

#include <TimerOne.h>

typedef struct data
{
  data(float roll=0.0f,float pitch=0.0f,float rw=0.0f,float pw=0.0f,float temp=0.0f,long lt=0);
  float Roll,Pitch,Roll_w,Pitch_w,temperature;
  unsigned long LastTime;
}data;
void WriteMPUReg(int nReg, unsigned char nVal);
unsigned char ReadMPUReg(int nReg);
void ReadAccGyr(int *pVals);
float GetRoll(float *pRealVals, float fNorm);
float GetPitch(float *pRealVals, float fNorm);
void Rectify(int *pReadout, float *pRealVals);

data getdata(data LastData);


