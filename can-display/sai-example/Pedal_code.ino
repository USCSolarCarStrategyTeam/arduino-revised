#include <mcp_can.h>
#include <SPI.h>

MCP_CAN CAN0(10);
int D5=5;
int flag_s=1;
float t1[51];
float t2[51];
float b[51];
float t1Avg=0.0;
float t2Avg=0.0;
float bAvg=0.0;
int n=0;
int j=0;
float t1Sum=0;
float t2Sum=0;
float bSum=0;
long unsigned int rxID;
unsigned char len=0;
unsigned char shutdown_test[1];
unsigned char encoder[3];
unsigned char rxBuf[8];
/*float t1[0]=0.0;
float t2[0]=0.0;
float b[0]=0.0;*/
void setup() {
Serial.begin(115200);
  // init can bus, baudrate: 500k
  if(CAN0.begin(CAN_500KBPS) == CAN_OK) Serial.println("\nCAN Init OK!!\r\n");
  else Serial.println("\nCAN Init Fail!!\r\n");
pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(D5,OUTPUT);
}

void loop() {
  read_can();
    if(flag_s!=1){
    shutdown_test[0]='C';
    CAN0.sendMsgBuf(0x02,0,1,&shutdown_test[0]);
    flag_s=1;}
  int startBtn=digitalRead(7);
  int buzzerOut=3;
t1Sum=0;
t2Sum=0;
bSum=0;
  float te1Val=analogRead(A0);
  float te2Val=analogRead(A1);
  float beVal=analogRead(A2);
    t1[j]=te1Val;
    t2[j]=te2Val;
    b[j]=beVal;
encoder[0]=te1Val;
encoder[1]=te2Val;
encoder[2]=beVal;    
CAN0.sendMsgBuf(0x10,0,3,encoder);
j++;
/*Serial.println("\nT1 Input:\t");
Serial.println(te1Val);
Serial.println("\nT2 Input:\t");
Serial.println(te2Val);
Serial.println("\nBE Input:\t");
Serial.println(beVal);*/
if(j==50){
for(int i=0;i<50;i++){
  Serial.println("\n Inside for Loop\n");
    t1Sum=t1Sum+t1[i];
    t2Sum=t2Sum+t2[i];
    bSum=bSum+b[i];
    t1Avg=t1Sum/50;
    t2Avg=t2Sum/50;
    bAvg=bSum/50;
    j=0;
  }
}
//delay(100);
float x=(t1Avg*5)/1023;
float y=(t2Avg*5)/1023;
float z=(bAvg*5)/1023;
Serial.println("\nTE 1 Average: \n");
Serial.println(x);

Serial.println("\nTE 2 Average: \n");
Serial.println(y);

Serial.println("\nBE Average: \n");
Serial.println(z);


if (x<1.2||x>4.9||y<1.2||y>4.9||z<1.2||z>4.9){
    Serial.println("\nEncoders out of Range\n");
    digitalWrite(5,LOW);
    //delay(2000);
  }
else{
    float d=0;
    if(x>y) d=x-y;
    if(x<y) d=y-x;
    if(d>0.5){
        Serial.println("\nTorque Plausibility\n");
        digitalWrite(5,LOW);
        //delay(2000);
      }
    else if(x>1.25&&z>0.2){
        Serial.println("\nTorque Brake Plausibilty\n");
        digitalWrite(5,LOW);
        //delay(2000);
        if(x<0.25){
            Serial.println("\nTorque Brake Plausibility Removed\n");
            digitalWrite(5,HIGH);
            //delay(2000);
          }
      }
    else{
        Serial.println("\nNo Plausibiity\n");
        digitalWrite(5,HIGH);
        //delay(2000);
      }
  }
}
void read_can(){
  CAN0.readMsgBuf(&len, rxBuf);              // Read data: len = data length, buf = data byte(s)
      rxID = CAN0.getCanId();
      if(rxID==0x01){
        if(rxBuf[0]=='N'){
          Serial.println("No fault - Main ECU");
          buzzer();
        }
        if(rxBuf[0]=='F'){
          Serial.println("Fault present - Main ECU");
        }
      }
}

