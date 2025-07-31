#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#include"can.h"
#include"can_defines.h"
volatile s32 i=0;
volatile s8 mode='X';
CANF rxf;
void leds_off(void)
{
    IOSET0=(255<<0);
}
int main()
{
 IODIR0|=255<<0;
    leds_off();
    init_CAN1();
    while(1)
    {
        if((C1GSR&(1<<RBS_BIT))!=0)
        {
           CAN1_rx(&rxf);
     if(rxf.ID==1)
     {
             mode=rxf.data1;
     }
        }
        switch(mode)
        {
          case'L':if(i<0 || i>7)
      {
       i=7;
      } 
      while(mode=='L')
      {
       i--;
     if(i<0)
     {
      i=7;
     }
       IOCLR0=(1<<i);
                    delay_ms(100);
                    IOSET0=(1<<i);
     if((C1GSR&(1<<RBS_BIT))!=0)
     {
      CAN1_rx(&rxf);
      if(rxf.ID==1)
      {
       mode=rxf.data1;
      }
     }
      }
      /**if(i>0)
      {
       i=i+1;
      } */
                     break;
             case'R':if(i<0 || i>7)
      {
       i=0;
      }
      while(mode=='R')
      {
       IOCLR0=(1<<i);
                    delay_ms(100);
                    IOSET0=(1<<i);
                    i++;
                    if(i>7)
     {
      i=0;
     }
     if(!(C1GSR&(1<<7)))
      {
      if((C1GSR&(1<<RBS_BIT))!=0)
      {
       CAN1_rx(&rxf);
       if(rxf.ID==1)
       {
        mode=rxf.data1;
       }
      }
     }
      }
      /**if(i>0)
      {
       i=i-1;
      } */
                  break;
          case'X':
          default:leds_off(); 
                  delay_ms(100);
                  break;
        }
    }
}