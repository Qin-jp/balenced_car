#pragma once

#include <TimerOne.h>


void Motor_setup();
int PID(float goal,float now);
void TimerIsr(int fLastRoll);
void Code0();
void Code1();


