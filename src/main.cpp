#include <Arduino.h>
#include<TLC5620.h>
#include <HID.h>
#include <EEPROM.h>
TLC5620 tlc5620(6, 7, 8, 9);
unsigned long push,set_add =0;
unsigned char OUT_RLY[65];
unsigned char cmd;
byte nhan,slave;
String add;


#define OUT1 2
#define OUT2 3
#define OUT3 4
#define OUT4 5
#define dir A4
// TLC5620::TLC5620(unsigned int DATA, unsigned int CLK, unsigned int LOAD, unsigned int LDAC)


void OUT_PUT(byte in)
{
 if(OUT_RLY[in]<10){
  digitalWrite(OUT1,0);
 }else{
   digitalWrite(OUT1,1);
   
 }

 if(OUT_RLY[in+1]<10){
  digitalWrite(OUT2,0);
 }else{
    digitalWrite(OUT2,1);
   
 }

  if(OUT_RLY[in+2]<10){
  digitalWrite(OUT3,0);
 }else{
    digitalWrite(OUT3,1);
   
 }

   if(OUT_RLY[in+3]<10){
  digitalWrite(OUT4,0);
 }else{
    digitalWrite(OUT4,1);
   
 }
// 26 53 00 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20
//  20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 20 25

 tlc5620.writeTLC5620(DACA, DAC_REFX2, OUT_RLY[in]);
 tlc5620.writeTLC5620(DACB, DAC_REFX2, OUT_RLY[in + 1]);
 tlc5620.writeTLC5620(DACC, DAC_REFX2, OUT_RLY[in + 2]);
 tlc5620.writeTLC5620(DACD, DAC_REFX2, OUT_RLY[in + 3]);
}
void setup() {
// put your setup code here, to run once:
// digitalWrite(OUT1,1);
// digitalWrite(OUT2,1);
// digitalWrite(OUT3,1);
// digitalWrite(OUT4,1);
pinMode(OUT1,OUTPUT);
pinMode(OUT2,OUTPUT);
pinMode(OUT3,OUTPUT);
pinMode(OUT4,OUTPUT);

digitalWrite(OUT1,1);
digitalWrite(OUT2,1);
digitalWrite(OUT3,1);
digitalWrite(OUT4,1);
delay(100);
digitalWrite(OUT1,0);
digitalWrite(OUT2,0);
digitalWrite(OUT3,0);
digitalWrite(OUT4,0);
Serial.begin(250000);
pinMode(dir,OUTPUT);
digitalWrite(dir,LOW);
//slave = (0<<7) | (0<<6) | (0<<5) | (1<<4) | (1<<3) | (1<<2) | (1<<1) | (1<<0);
slave = EEPROM.read(200);
if(slave >=65)slave = 63;
Serial.println(slave);
 tlc5620.initTLC5620();
}

void loop() {
  // put your main code here, to run repeatedly:
//  tlc5620.writeTLC5620(DACA, DAC_REFX2,255);
 while (Serial.available() > 0) {
    //------------------------------------------- doc du lieu dau vao nhan duoc
    char in = Serial.read(); 
//  #Setaddress^4^17*
     if (in =='#' && nhan ==0 ) nhan = 1;
     else    
      if (in =='S' && nhan ==1 ) nhan = 2;
      else    
      if (in =='e' && nhan ==2 ) nhan = 3;
      else    
      if (in =='t' && nhan ==3 ) nhan = 4;
      else    
      if (in =='a' && nhan ==4 ) nhan = 5;
      else    
      if (in =='d' && nhan ==5 ) nhan = 6;
      else    
      if (in =='d' && nhan ==6 ) nhan = 7;
      else    
      if (in =='r' && nhan ==7 ) nhan = 8;
      else    
      if (in =='e' && nhan ==8 ) nhan = 9;
      else    
      if (in =='s' && nhan ==9 ) nhan = 10;
      else    
      if (in =='s' && nhan ==10 ) nhan = 11;
      else    
      if (in =='^' && nhan ==11 ) nhan = 12;
       else    
       
      if (  nhan == 12 ){
           add += in;      
//           Serial.println(in); 
           nhan = 13;
           }
           else
      
           if ( nhan == 13 ){
           add += in;  
//           Serial.println(add);
            if (add.toInt() == slave)
         {
//          slave = add.toInt();
//          Serial.print("nhan duwojc");Serial.print(slave); 
          nhan = 14 ;       
          add ="";
         } else {
          nhan=0;
          add ="";     
         }
           }
                else
         
      
          
       
      if (in =='^' && nhan ==14 )
      {
        nhan = 15;
        
      }
       else    
      if ( nhan ==15 ) 
      {
        nhan = 16;
        add += in;
//       Serial.println(add);
      }
      else
        
         if (nhan == 16   ) 
         { 
           nhan = 17;   
           add += in;
//           Serial.println(add);       
//         
         }
         else
         

             
         if (nhan == 17   && in == '*' ) 
         { 
           nhan = 0;   

//           Serial.println(add);       
           slave = add.toInt();

           EEPROM.write(200,slave);
           add ="";
           
         }
         
        
         
         
    //-------------------------------------------- bat dau xu ly
    //-------------- Ký tự bắt đầu
    if (in == '&') {cmd=1;} 
    else if (cmd==1 && in == 'S') {cmd=2;}
    else if (cmd==2)  { OUT_RLY[0]=in; cmd=3;}
    else if (cmd==3)  { OUT_RLY[1]=in; cmd=4;}
    else if (cmd==4)  { OUT_RLY[2]=in; cmd=5;}
    else if (cmd==5)  { OUT_RLY[3]=in; cmd=6;}
    else if (cmd==6)  { OUT_RLY[4]=in; cmd=7;}
    else if (cmd==7)  { OUT_RLY[5]=in; cmd=8;}
    else if (cmd==8)  { OUT_RLY[6]=in; cmd=9;}
    else if (cmd==9)  { OUT_RLY[7]=in; cmd=10;}
    else if (cmd==10)  { OUT_RLY[8]=in; cmd=11;}
    else if (cmd==11)  { OUT_RLY[9]=in; cmd=12;}
    else if (cmd==12)  { OUT_RLY[10]=in; cmd=13;}
    else if (cmd==13)  { OUT_RLY[11]=in; cmd=14;}
    else if (cmd==14)  { OUT_RLY[12]=in; cmd=15;}
    else if (cmd==15)  { OUT_RLY[13]=in; cmd=16;}
    else if (cmd==16)  { OUT_RLY[14]=in; cmd=17;}
    else if (cmd==17)  { OUT_RLY[15]=in; cmd=18;}
    else if (cmd==18)  { OUT_RLY[16]=in; cmd=19;}
    else if (cmd==19)  { OUT_RLY[17]=in; cmd=20;}
    else if (cmd==20)  { OUT_RLY[18]=in; cmd=21;}
    else if (cmd==21)  { OUT_RLY[19]=in; cmd=22;}
    else if (cmd==22)  { OUT_RLY[20]=in; cmd=23;}
    else if (cmd==23)  { OUT_RLY[21]=in; cmd=24;}
    else if (cmd==24)  { OUT_RLY[22]=in; cmd=25;}
    else if (cmd==25)  { OUT_RLY[23]=in; cmd=26;}
    else if (cmd==26)  { OUT_RLY[24]=in; cmd=27;}
    else if (cmd==27)  { OUT_RLY[25]=in; cmd=28;}
    else if (cmd==28)  { OUT_RLY[26]=in; cmd=29;}
    else if (cmd==29)  { OUT_RLY[27]=in; cmd=30;}
    else if (cmd==30)  { OUT_RLY[28]=in; cmd=31;}
    else if (cmd==31)  { OUT_RLY[29]=in; cmd=32;}
    else if (cmd==32)  { OUT_RLY[30]=in; cmd=33;}
    else if (cmd==33)  { OUT_RLY[31]=in; cmd=34;}
     
         // them moi phan nay ne
        else if (cmd==34)  { OUT_RLY[32]=in; cmd=35;}
        else if (cmd==35)  { OUT_RLY[33]=in; cmd=36;}       
        else if (cmd==36)  { OUT_RLY[34]=in; cmd=37;}
        else if (cmd==37)  { OUT_RLY[35]=in; cmd=38;}
        else if (cmd==38)  { OUT_RLY[36]=in; cmd=39;}     
        else if (cmd==39)  { OUT_RLY[37]=in; cmd=40;}
        else if (cmd==40)  { OUT_RLY[38]=in; cmd=41;}
        else if (cmd==41)  { OUT_RLY[39]=in; cmd=42;}
        else if (cmd==42)  { OUT_RLY[40]=in; cmd=43;}
        else if (cmd==43)  { OUT_RLY[41]=in; cmd=44;}
        else if (cmd==44)  { OUT_RLY[42]=in; cmd=45;}
        else if (cmd==45)  { OUT_RLY[43]=in; cmd=46;}
        else if (cmd==46)  { OUT_RLY[44]=in; cmd=47;}
        else if (cmd==47)  { OUT_RLY[45]=in; cmd=48;}
        else if (cmd==48)  { OUT_RLY[46]=in; cmd=49;}
        else if (cmd==49)  { OUT_RLY[47]=in; cmd=50;}
        else if (cmd==50)  { OUT_RLY[48]=in; cmd=51;}
        else if (cmd==51)  { OUT_RLY[49]=in; cmd=52;}
        else if (cmd==52)  { OUT_RLY[50]=in; cmd=53;}
        else if (cmd==53)  { OUT_RLY[51]=in; cmd=54;}
        else if (cmd==54)  { OUT_RLY[52]=in; cmd=55;}
        else if (cmd==55)  { OUT_RLY[53]=in; cmd=56;}
        else if (cmd==56)  { OUT_RLY[54]=in; cmd=57;}
        else if (cmd==57)  { OUT_RLY[55]=in; cmd=58;}
        else if (cmd==58)  { OUT_RLY[56]=in; cmd=59;}
        else if (cmd==59)  { OUT_RLY[57]=in; cmd=60;}
        else if (cmd==60)  { OUT_RLY[58]=in; cmd=61;}
        else if (cmd==61)  { OUT_RLY[59]=in; cmd=62;}
        else if (cmd==62)  { OUT_RLY[60]=in; cmd=63;}
        else if (cmd==63)  { OUT_RLY[61]=in; cmd=64;}
        else if (cmd==64)  { OUT_RLY[62]=in; cmd=65;}
        else if (cmd==65)  { OUT_RLY[63]=in; cmd=66;}

        
    else if (cmd==66 && in=='%')
      {
        // OUT_PUT(OUT_RLY[slave]);
         OUT_PUT(slave);
        cmd=0;
      } 
//      ----------------------------

    
     
   
// ------------------------------------
   
    else cmd=0;

//    /-----------------
 push = millis();
  }
  
if ((unsigned long) (millis() - push) >= 1000) {
  digitalWrite(dir,HIGH);
  
   Serial.print('#'); Serial.print(slave); Serial.print('*');
   delay(10);
   digitalWrite(dir,LOW);
   push = millis();
}
  
}
