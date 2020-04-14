#include <Arduino.h>
#include <stdint.h>
#include "Linduino.h"
#include "LT_SPI.h"
#include "UserInterface.h"
#include "LTC68041.h"
#include <SPI.h>

const uint8_t TOTAL_IC = 10;

uint8_t flag = 0;

uint8_t sum = 0;

uint8_t pflag = 0;

uint16_t cell_codes[TOTAL_IC][12];

uint8_t tx_cfg[TOTAL_IC][6];

uint8_t rx_cfg[TOTAL_IC][8];

void setup()
{
  Serial.begin(115200);
  LTC6804_initialize(); 
  init_cfg();
  pinMode(3, OUTPUT);
  digitalWrite(3,LOW);
}
void loop()
{
    run_command();
}


void run_command()
{
      int8_t error = 0;
      char input = 0;
      wakeup_sleep();
      LTC6804_wrcfg(TOTAL_IC,tx_cfg);
      while (1)
      {
        wakeup_idle();
        LTC6804_adcv();
        delay(10);
        wakeup_idle();
        error = LTC6804_rdcv(0, TOTAL_IC,cell_codes);
      if(pflag < 5)
       {
        if (error == -1)
        {
         pflag = pflag + 1;
        }
        else
        {
          pflag = 0; 
          print_cells();    
        }
        delay(200);
       }
      else
       {
        digitalWrite(3,HIGH);
        Serial.println("000000000000000000000000000000000000000010");
        Serial.println("000000000000000000000000000000000000000011");
        Serial.println("000000000000000000000000000000000000000012");
        Serial.println("000000000000000000000000000000000000000013");
        Serial.println("000000000000000000000000000000000000000014");
        Serial.println("000000000000000000000000000000000000000015");
        Serial.println("000000000000000000000000000000000000000016");
        Serial.println("000000000000000000000000000000000000000017");    
        pflag = pflag - 1;
       }
    }
      
}


void init_cfg()
{
  for (int i = 0; i<TOTAL_IC; i++)
  {
    tx_cfg[i][0] = 0xFE;
    tx_cfg[i][1] = 0x00 ;
    tx_cfg[i][2] = 0x00 ;
    tx_cfg[i][3] = 0x00 ;
    tx_cfg[i][4] = 0x00 ;
    tx_cfg[i][5] = 0x00 ;
  }

}

void print_cells()
{
   int x;
   sum = 0;
  for (int current_ic = 0 ; current_ic < TOTAL_IC; current_ic++)
  { 
    flag = 0; 
    for (int i=0; i<10; i++)
    {
     x =  cell_codes[current_ic][i]*0.1;
     Serial.print(x);
     if((cell_codes[current_ic][i]*0.1)>4200||(cell_codes[current_ic][i]*0.1)<3100)
      {
       flag = 1;   
      }
    }
    if(flag==1)
    {
     Serial.print(1);
    }
    else
    {
    Serial.print(0);
    }
    Serial.println(current_ic);
    delay(80);
    sum = sum + flag;
  }
  if(sum >= 1)
  {
   digitalWrite(3,HIGH);  
  }  
  else
  {
   digitalWrite(3,LOW);  
  }
}



void serial_print_hex(uint8_t data)
{
  if (data< 16)
  {
    Serial.print("0");
    Serial.print((byte)data,HEX);
  }
  else
    Serial.print((byte)data,HEX);
}
