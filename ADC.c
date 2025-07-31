#include<LPC21xx.h>
#include "ADC1_defines.h"
#include "types.h"
#include "delay.h"
//volatile u32 adcval;
void init_ADC(void)
{
 PINSEL1=((PINSEL1&~(3<<24))|(1<<24));
 ADCR=(1<<PDN)|(CLKDIV<<CLKDIV_BITS);
}

void read_adc1(u8 ch, u32 *adcval, f32 *ear)
{
 ADCR&=0XFFFFFF00;
 ADCR|=1<<ch;
 ADCR|=1<<24;
 delay_us(3);
 while(((ADDR>>DONEBIT)&1)==0);
 ADCR&=~(1<<24);
 *adcval=((ADDR>>DIGDATA)&1023);
 ear=(3.3/1023)(*adcval);
}
