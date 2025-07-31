
#include<LPC21xx.h>
#include"types.h"
#include"delay.h"
#include"lcd_defines.h"
void WriteLCD(u8 byte)
{
 IOCLR0=1<<LCD_RW;
 IOPIN0=((IOPIN0&~(0xFF<<LCD_DATA))|(byte<<LCD_DATA));
 IOSET0=1<<LCD_EN;
 delay_ms(1);
 IOCLR0=1<<LCD_EN;
 delay_ms(2);
}
void CmdLCD(u8 cmd)
{
 IOCLR0=1<<LCD_RS;
 WriteLCD(cmd);
}
void CharLCD(u8 ascii)
{
 IOSET0=1<<LCD_RS;
 WriteLCD(ascii);
}
void InitLCD(void)

{
 IODIR0|=((0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
 delay_ms(15);
 CmdLCD(0x30);
 CmdLCD(0x30);
 CmdLCD(0x30);
 CmdLCD(MODE_8BIT_2LINE);
 CmdLCD(DSP_ON_CUR_OFF);
 //CmdLCD(CLEAR_LCD);
 //CmdLCD(SHIFT_CUR_RIGHT);
}
void StrLCD(u8 *s)
{
 while(*s)
 {
  CharLCD(*s++);
 }
}
void U32LCD(u32 n)
{
 s32 i=0;
 u8 digit[10];
 if(n==0)
 {
  CharLCD('0');
 }
 else
 {
  while(n>0)
  {
   digit[i]=(n%10)+48;
   n=n/10;
   i++;
  }
  for(i=i-1; i>=0; i--)
  {
   CharLCD(digit[i]);
  }
 }
}
void S32LCD(s32 n)
{
 if(n<0)
 {
  CharLCD('-');
  n=-n;
 }
 U32LCD(n);
}
void F32LCD(f32 fNUM, u8 nDP)
{
 s32 i;
 u32 n;
 if(fNUM<0)
 {
  CharLCD('-');
  fNUM=-fNUM;
 }
 n=fNUM;
 U32LCD(n);
 CharLCD('.');
 for(i=0; i<nDP; i++)
 {
  fNUM=(fNUM-n)*10;
  n=fNUM;
  CharLCD(n+'0');
 }
}