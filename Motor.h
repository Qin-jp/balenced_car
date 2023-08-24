#pragma once

#include <TimerOne.h>


void Motor1_setup();
int PID1(float goal,float now);
void Balance1(int fLastRoll);
// void Code0();//不一定用得到
// void Code1();

void Motor2_setup();
int PID2(float goal,float now);
void Balance2(int fLastRoll);
