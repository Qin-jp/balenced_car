#include"connect_to_rocker.h"

SoftwareSerial BTserial(6, 7); // RX | TX
long x=0,y=0;

BTdata::BTdata(int xx,int yy)
{
  x=xx,y=yy;
}
bool BTdata::operator!=(BTdata bt2)
{
  if(this->x!=bt2.x)
  {
    return true;
  }
  else if(this->y!=bt2.y)
  {
    return true;
  }
  return false;
}

void setupBT()
{
    // start th serial communication with the host computer
    Serial.begin(9600);
    Serial.println("Arduino with HC-05 is ready");
    // start communication with the HC-05 using 57600
    BTserial.begin(57600);  
    Serial.println("BTserial started at 57600");

}

BTdata getBTdata()
{
  // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {
        char c = BTserial.read();
        if(c=='x')
        {
          delay(10);
          if(BTserial.available())
          {
          x=BTserial.parseInt();
          y=BTserial.parseInt(); 
          BTdata btdata(x,y);
          Serial.print(" x:");  
          Serial.print(x);
          Serial.print("\n"); 
          Serial.print(" y:");  
          Serial.print(y);        
          Serial.print("\n");   
          return btdata;
          }
        }       
    } 
    return NULLBTDATA;//如果获取不到数据就返回这个错误数据
}