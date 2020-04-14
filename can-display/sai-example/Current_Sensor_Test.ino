#include <mcp_can.h>
#include <SPI.h>
int Main_CS_Pin=10;
MCP_CAN CAN0(Main_CS_Pin);                                      // Set CS to pin 10


unsigned long current_time_ct;
unsigned long last_time_ct;
const int XOR_In1=6;
const int XOR_In2=7;

const int Current_SensePin1=A0;
const int Current_SensePin2=A1;
const int Current_SensePin3=A2;
const int Voltage_SensePin=A3;
const int hole_number=10;
int Speed_Sense_Pin_L=8;
int Speed_Sense_Pin_R=9;


float Current_Sense1;
float Current_Sense2;
float Current_Sense3;

float Voltage_Sense;

float Current1;
float Current2;
float Current3;
float Voltage;

float lin_speed_kmph;

int State1;
int State2;

unsigned char CSend[8];

const long time_period=0.01;
const int time_period_prox=1000;

unsigned long last_time_prox;
unsigned long current_time_prox;

int temp1,last_temp_1;
int temp2,last_temp_2;
int deb_timer_1,deb_timer_2;
float count_1,count_2;
float rot,lin_vel;
float radius_wheel=0.1875;



void setup() {
//Current
pinMode(XOR_In1,OUTPUT);
pinMode(XOR_In2,OUTPUT);
pinMode(Current_SensePin1,INPUT);
pinMode(Current_SensePin2,INPUT);
pinMode(Current_SensePin3,INPUT);
pinMode(Voltage_SensePin,INPUT);

State1=HIGH;
State2=LOW;

//Proximity
pinMode(Speed_Sense_Pin_L,INPUT);
pinMode(Speed_Sense_Pin_R,INPUT);

last_time_prox=0;
last_temp_1=0;
last_temp_2=0;
count_1=0;
count_2=0;
Serial.begin(115200);

if(CAN0.begin(CAN_500KBPS) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");

}

void loop() 
{
//Current
  // put your main code here, to run repeatedly:
Current_Sense1=analogRead(Current_SensePin1);
Current_Sense2=analogRead(Current_SensePin2);
Current_Sense3=analogRead(Current_SensePin3);
Voltage_Sense=analogRead(Voltage_SensePin);

Current_Sense1=(5*Current_Sense1/1024)-2.5;
if (Current_Sense1>=0)
   Current1=map(Current_Sense1,0,2.5,0,100);
else if(Current_Sense1<0)
   Current1=map(Current_Sense1,-2.5,0,-100,0);

Current_Sense2=(5*Current_Sense2/1024)-2.5;
if (Current_Sense2>=0)
   Current2=map(Current_Sense2,0,2.5,0,100);
else if(Current_Sense2<0)
   Current2=map(Current_Sense2,-2.5,0,-100,0);

Current_Sense3=(5*Current_Sense3/1024)-2.5;
if (Current_Sense3>=0)
   Current3=map(Current_Sense3,0,2.5,0,100);
else if(Current_Sense3<0)
   Current3=map(Current_Sense3,-2.5,0,-100,0);
Voltage=Voltage_Sense*300/1024;


Serial.print(Current1);
Serial.print("         ");
Serial.print(Current2);
Serial.print("         ");
Serial.print(Current3);
Serial.print("         ");
Serial.println(Voltage);


current_time_ct=millis();
current_time_prox=millis();


if ((abs(Current1-Current2)>10)||(abs(Current2-Current3)>10)||(abs(Current3-Current1)>10))
{
  if (State1==HIGH)
  State2=LOW;
  else
  State2=HIGH;

}
else
{
  State2=State1;
}
  if (current_time_ct-last_time_ct>=time_period)
  {
  last_time_ct=current_time_ct;
  if (State1==HIGH)
  {
  State1=LOW;
  }
  else
  {
  State1=HIGH;
  }
  }
  digitalWrite(XOR_In1,State1);
  digitalWrite(XOR_In2,State2);

int temp_state_1,temp_state_2;
if (current_time_prox-last_time_prox<time_period_prox)
  {
    temp1=digitalRead(Speed_Sense_Pin_L);
    temp2=digitalRead(Speed_Sense_Pin_R);
    if (temp1 != last_temp_1)
      deb_timer_1=millis();

    if (temp2 != last_temp_2)
      deb_timer_2=millis();

        
    if (millis()-deb_timer_1>10)
    {
      if (temp1!=temp_state_1)
      {
       temp_state_1=temp1;
      
      if (temp_state_1==LOW)
          count_1=count_1+1;
      }
    }

        if (millis()-deb_timer_2>10)
    {
      if (temp2!=temp_state_2)
      {
       temp_state_2=temp2;
      
      if (temp_state_2==LOW)
          count_2=count_2+1;
      }
    }

    last_temp_1=temp1;
    last_temp_2=temp2;
  }
  else
  {
    rot=(count_1+count_2)/(2*hole_number);
    lin_vel=rot*2*3.14*radius_wheel;
    lin_speed_kmph=lin_vel*18/5;
  Serial.println(lin_speed_kmph);
  last_time_prox=current_time_prox;
  count_1=0;
  count_2=0;
  }
Current1=(int)Current1;
Current2=(int)Current2;
Current3=(int)Current3;
Voltage=(int)Voltage;
lin_speed_kmph=(int)lin_speed_kmph;

 CSend[0]=(unsigned char)Current1;
 CSend[1]=(unsigned char)Current2;
 CSend[2]=(unsigned char)Current3;
 CSend[3]=(unsigned char)Voltage;
 CSend[4]=(unsigned char)lin_speed_kmph;

  
  Serial.print(CSend[0]);
  Serial.print(",");
  Serial.print(CSend[1]);
  Serial.print(",");
  Serial.print(CSend[2]);
  Serial.print(",");
  Serial.print(CSend[3]);
  Serial.print(",");
  Serial.println(CSend[4]);
   
  CAN0.sendMsgBuf(0x00, 0, 5, CSend);  
  delay(100);  
}


