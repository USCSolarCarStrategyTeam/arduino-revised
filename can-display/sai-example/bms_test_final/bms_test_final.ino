#include <Arduino.h>
#include <stdint.h>
#include "Linduino.h"
#include "LT_SPI.h"
#include "UserInterface.h"
#include "LTC68041.h"
#include <SPI.h>

const uint8_t TOTAL_IC = 8;

uint8_t flag = 0;

uint8_t uflag = 0;

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
        if (error == -1)
        {
          digitalWrite(3, HIGH);
        }
        else
        {
          digitalWrite(3, LOW);
          print_cells();
        }
        delay(200);
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
   //  digitalWrite(3, HIGH);
    }
    else
    {
    Serial.print(0);
    digitalWrite(3, LOW);
    }
    Serial.println(current_ic);
    delay(80);
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
