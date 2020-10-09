
#include<UTFT.h>
#include<UTouch.h>
UTFT Screen(ITDB32S,38,39,40,41);

extern uint8_t BigFont[];
extern uint8_t SevenSeg_XXXL_Num[];
//extern unsigned int tux[0x1000];
int Torque=0;
void drawRevMeter()
{
  

if (Torque>=1)
{
  Screen.setColor(0,0,0);
  Screen.fillRect(15,10,60,220);
  Screen.setColor(0,255,27);
  Screen.fillRect(15,170,60,220);

  if (Torque>=2)
  {
  Screen.setColor(246,255,0);
  Screen.fillRect(15,120,60,170);
  if (Torque>=3)
  {
  Screen.setColor(255,126,0);
  Screen.fillRect(15,70,60,120);
  
  if (Torque>=4)
  {
  Screen.setColor(255,65,11);
  Screen.fillRect(15,40,60,70);
  
  if (Torque>=5)
  {
  Screen.setColor(255,0,0);
  Screen.fillRect(15,10,60,40);
  }
  }
  }
  }
}
}


void Speedometer(int Speed)
{
  Screen.setColor(255,255,255);
  Screen.setFont(BigFont);
  Screen.print("Speed",120,40);
    
  Screen.setColor(255,255,255);
  Screen.setFont(SevenSeg_XXXL_Num);

  Screen.printNumI(Speed,90,70);
}

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
Screen.InitLCD();
Screen.clrScr();

//Screen.drawBitmap(0,0,64,64,tux,1);
//delay(5000);
pinMode(A1,INPUT);
Screen.setBackColor(0,0,0);
Screen.setFont(BigFont);
Screen.setColor(255,255,255);
Screen.print("TEAM OJAS",70,110);
delay(3000);
Screen.clrScr();

drawRevMeter();  
Speedometer(0);
}



void loop() {
  int Speed_Sensor_Val;
  //Torque=map(analogRead(A0),0,512,0,6);
  Torque=random(1,6);
  drawRevMeter();
  delay(150);
 //  Speed_Sensor_Val=map(analogRead(A1),0,512,0,120);;
Speed_Sensor_Val=random(0,70);
  Speedometer(Speed_Sensor_Val);
   
  // put your main code here, to run repeatedly:

}
