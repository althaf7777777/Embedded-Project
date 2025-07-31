#include <lpc21xx.h>
#include "types.h"
#include "ADC1_defines.h"
#include "can.h"
#include"can_defines.h"
#include "delay.h"
#define Min 0.43
#define Max 2.45
void init_ADC(void);
void read_adc1(u8 ch, u32 *adcval, f32 *ear);
u32 adcval,per;
f32 ear;
u8 ReadFuelSensor()
{
 read_adc1(1,&adcval,&ear);
 per=((ear-Min)/(Max-Min))*100;
 return per;
}
int main()
{
 CANF txf;
 init_ADC();       
 init_CAN1();
 while (1) 
 {
    u8 fuel=ReadFuelSensor();
  if(fuel>100)
  {
   fuel=100;
  }  
  txf.ID=2;  
  txf.bfv.RTR=0;    
  txf.data1=fuel;        
     txf.bfv.DLC=1;    
  CAN1_tx(txf);
  delay_ms(200); 
   }    
}