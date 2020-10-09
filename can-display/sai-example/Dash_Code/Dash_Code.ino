#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SPI.h>
#include <mcp_can.h>

const int SPI_CS_PIN = 9;
const int TFT_DC = 6;
const int TFT_CS = 10;
const int REV_PIN = A1;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
int v_green,v_yellow,v_red;

int id;
float refresh_rate=50;
MCP_CAN CAN0(SPI_CS_PIN);                                    // Set CS pin
int voltage;
int lin_vel_kmph;
void setup()
{

    tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextWrap(false);
  tft.setCursor(100,10);
  tft.setTextColor(ILI9341_WHITE,ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("Team Ojas");
  tft.drawRect(33,1,285,238,ILI9341_GREEN);
  tft.setCursor(100,50);
  tft.println("Speed: ");
  tft.setTextSize(2);
  tft.setCursor(180,100);
  tft.print("kmph");
  
  tft.setCursor(100,150);
  tft.println("SOC: ");

/* tft.begin();
 tft.setRotation(1);
 tft.fillScreen(ILI9341_BLACK);
 tft.drawRect(5,5,310,230,ILI9341_BLUE);
 tft.setCursor(30,100);
 tft.setTextColor(ILI9341_WHITE);
 tft.setTextSize(5);
 tft.println("TEAM OJAS");
 delay(4000);
tft.fillScreen(ILI9341_BLACK);
 tft.drawRect(5,5,310,230,ILI9341_BLUE);
*/



    Serial.begin(115200);
Serial.println("Hello");
if(CAN0.begin(CAN_500KBPS) == CAN_OK) 
      Serial.print("can init ok!!\r\n");
  else 
      Serial.print("Can init fail!!\r\n");
  pinMode(2,INPUT);
  delay(50);

     Serial.println("Initializing Card");
  //CS Pin is an output
 
  
  //SD Card will Draw Power from Pin 8, so set it high
  
  //Initialize Card

  //Write Log File Header
}

void loop()
{
can_read_sd_store(); 
    
//tft.fillScreen(ILI9341_BLACK);

  disp_soc(voltage);
/* tft.setCursor(120,80);
 tft.setTextSize(7);
 tft.setTextColor(ILI9341_WHITE);*/
tft.setTextSize(5);
tft.setCursor(100,80);

  if(lin_vel_kmph<10) 
    tft.print("0");
 else
 {
  }
/*    tft.println(lin_vel_kmph);
 tft.setCursor(100,20);
 tft.setTextSize(2);
 tft.println("TEAM OJAS");
 tft.setCursor(120,60);
 tft.println("SPEED:");
 delay(500);
 tft.fillRect(100,80,140,80,ILI9341_BLACK);
*/
tft.println(lin_vel_kmph);

}


void can_read_sd_store()
{
    unsigned char len = 0;
    unsigned char buf[8];
  
        if(!digitalRead(2))                         // If pin 2 is low, read receive buffer
    {
        CAN0.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN0.getCanId();
        if (canId==0x00)
        {
        Serial.println("-----------------------------");
        Serial.print("get data from ID: ");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i],DEC);
            Serial.print("\t");
         }
         
        //Create Data string for storing to SD card
  //We will use CSV Format  
        
        voltage=map((int)buf[0],0,168,0,4);
   
            lin_vel_kmph=(int)buf[1];

            
   // Serial.println(dataString);
      } 
    else if (canId==0x10)
    {
      int rev=(int)buf[0];
      Serial.println(rev);
      analogWrite(A1,rev);
    }
    
  }
  
}
void disp_soc(int soc)
{
    if(soc <= 1){
      tft.fillRect(0,0,32,240,ILI9341_BLACK);
      tft.fillRect(0, 180, 32, 60, ILI9341_RED);
    }
    else if(soc <= 2){
      tft.fillRect(0,0,32,240,ILI9341_BLACK);
      tft.fillRect(0, 180, 32, 60, ILI9341_RED);
      tft.fillRect(0, 120, 32, 60, ILI9341_ORANGE);
    }
    else if(soc <= 3){
      
      tft.fillRect(0,0,32,240,ILI9341_BLACK);
      tft.fillRect(0, 180, 32, 60, ILI9341_RED);
      tft.fillRect(0, 120, 32, 60, ILI9341_ORANGE);
      tft.fillRect(0, 60, 32, 60, ILI9341_YELLOW);
    }
    else{
      
      tft.fillRect(0, 180, 32, 60, ILI9341_RED);
      tft.fillRect(0, 120, 32, 60, ILI9341_ORANGE);
      tft.fillRect(0, 60, 32, 60, ILI9341_YELLOW);
      tft.fillRect(0, 0, 32, 60, ILI9341_GREEN);
    }
  
}
/*  v_green=90;
  v_yellow=60;
  v_red=20;
  
  int y=map(voltage,0,100,200,10);
   if (voltage>v_green)
   {
     tft.fillRect(10,40+190*((100-voltage)/100),50,190*voltage/100,ILI9341_GREEN);
     tft.fillRect(260,40+190*((100-voltage)/100),50,190*voltage/100,ILI9341_GREEN);
   }
   if (voltage>v_yellow&& voltage<v_green)
   {
     tft.fillRect(10,116+114*(60-voltage)/60,50,114*voltage/60,ILI9341_YELLOW);
     tft.fillRect(260,116+114*(60-voltage)/60,50,114*voltage/60,ILI9341_YELLOW);
   }
   if (voltage>v_red && voltage<v_yellow)
   {
      tft.fillRect(10,192+38*(20-voltage)/20,50,38*voltage/20,ILI9341_RED);
      tft.fillRect(260,192+38*(20-voltage)/20,50,38*voltage/20,ILI9341_RED);
   }
   tft.setCursor(17,20+190*(100-voltage)/100);
   tft.setTextSize(3);
   tft.println(voltage);

*/
