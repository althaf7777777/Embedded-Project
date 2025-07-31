
#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"lcd_defines.h"
#include"lcd.h"
#include"i2c.h"
#include"lcd.h"
#include"can.h"
#include"can_defines.h"
#include"lcd_defines.h"
#include"i2c_defines.h"
#define THRESHOLD 19
void init_MMA7660()
{
 i2c_start();
 i2c_write(0x98);
 i2c_write(0x07);
 i2c_write(0x01);
 i2c_stop();
}
u8 read_MMA7660(u8 reg)
{
 u8 data;
 i2c_start();
 i2c_write(0x98);
 i2c_write(reg);
 i2c_restart();
 i2c_write(0x99);
 data=i2c_nack();
 if(data>31)
 {
  data=data-64;
 }
 i2c_stop();
 delay_ms(10);
 return data;
}
s8 x,y,z;
volatile u32 flag=0;       
u32 count=0;
u8 current=0;
volatile u32 per;
void eint0_isr() __irq
{
 flag=1;
 EXTINT=1<<0;
 VICVectAddr=0;
}
void eint3_isr() __irq
{
 flag=2;
 EXTINT=1<<3;
 VICVectAddr=0;
}
int main()
{
 CANF txf;
 CANF rxf;
 init_i2c();
 init_MMA7660();
 InitLCD();
 init_CAN1();
 txf.ID=1;
 txf.bfv.RTR=0;
 PINSEL0=((PINSEL0&~(3<<2))|(3<<2));
 PINSEL1=((PINSEL1&~(3<<((20%16)*2)))|(3<<((20%16)*2)));
	
 VICIntSelect=0;
 VICIntEnable=1<<14|1<<17;
 VICVectCntl0=1<<5|14;
 VICVectAddr0=(u32)eint0_isr;

 VICVectCntl1=1<<5|17;
 VICVectAddr1=(u32)eint3_isr;
 EXTINT=0;
 EXTMODE=1<<3|1<<0;
 EXTPOLAR=0;
 while(1)
 {
  if(((C1GSR>>0)&1))
  {
      CAN1_rx(&rxf);    
      if(rxf.ID==2 && rxf.bfv.DLC>=1)
    {
     per=rxf.data1; 
        CmdLCD(GOTO_LINE2_POS0);
    StrLCD("FUEL:");
    if(per<=9 || per<=99)
    {
     CmdLCD(GOTO_LINE2_POS0+5);
     StrLCD(" ");
    }
    CmdLCD(GOTO_LINE2_POS0+5);
    //StrLCD(" ");
    U32LCD(per); 
    //delay_ms(500); //added
    CharLCD(0x25);
   }
  }
  
  CmdLCD(0x80+12);
  x=read_MMA7660(0x00);
  y=read_MMA7660(0x01);
  z=read_MMA7660(0x02);
  if(flag!=0)
  {
   if(flag==current)
   {
    txf.data1='X';
          txf.bfv.DLC=1;
          CAN1_tx(txf);
    CmdLCD(0x80+12);
    StrLCD(" ");
    current=0;
   }
   else
   {
    if(flag==1)
    {
     txf.data1='L';
     //CmdLCD(0x80+12);
     //StrLCD(" ");
     CmdLCD(0x80+12);
     CharLCD('R');
    }
    else if(flag==2)
    {
     txf.data1='R';
     //CmdLCD(0x80+12);
     //StrLCD(" ");
     CmdLCD(0x80+12);
     CharLCD('L');
    }
    txf.bfv.DLC = 1;
          CAN1_tx(txf);
    current=flag;
   }
   flag=0;
  }
  if(x>THRESHOLD||x<(-THRESHOLD)||y>THRESHOLD||y<(-THRESHOLD)||z>THRESHOLD||z<(-THRESHOLD))
  {
   StrLCD(" ");
   CmdLCD(0x80); 
   StrLCD("AirBagOpen");
  }
  else
  {
   CmdLCD(0x80);
   StrLCD(" ");
   CmdLCD(0x80);
   StrLCD("Safe");
  }
  delay_ms(500);
 }
}

