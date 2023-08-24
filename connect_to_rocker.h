#pragma once

#include <SoftwareSerial.h>
#include"HardwareSerial.h"
#include"Arduino.h"
#define  NULLBTDATA (BTdata(-1,-1))

typedef struct BTdata
{
  BTdata(int xx,int yy);
  bool operator!=(BTdata);
  int x;
  int y;

}BTdata;

void setupBT();

BTdata getBTdata();

