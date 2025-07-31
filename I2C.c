#include<lpc21xx.h>
#include"types.h"
#define I2C_SPEED 100000
#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)
#define BITRATE ((PCLK/I2C_SPEED)/2)
#define I2EN_BIT 6
#define STA_BIT 5
#define STO_BIT 4
#define STAC_BIT 5
#define I2_SIC 3
#define SI_BIT 3
#define SIC_BIT 3
#define AA_BIT 2
#define AAC_BIT 2
#define I2_EN_CLR 5
void init_i2c()
{
 PINSEL0=((PINSEL0&~(3<<4))|(1<<4));
 PINSEL0=((PINSEL0&~(3<<6))|(1<<6));
 I2SCLL=BITRATE;
 I2SCLH=BITRATE;
 I2CONSET=(1<<I2EN_BIT); 
}
void i2c_start()
{
 I2CONSET=1<<STA_BIT;
 while(((I2CONSET>>SI_BIT)&1)==0);
 I2CONCLR=1<<STAC_BIT;
}
void i2c_stop()
{
 I2CONSET=1<<STO_BIT;
 I2CONCLR=1<<SIC_BIT;
}
void i2c_write(u8 data)
{
 I2DAT=data;
 I2CONCLR=1<<SIC_BIT;
 while(((I2CONSET>>SI_BIT)&1)==0);
}
u8 i2c_nack()
{
 I2CONCLR=1<<SIC_BIT;
 while(((I2CONSET>>SI_BIT)&1)==0);
 return I2DAT;
}
u8 i2c_mack()
{
 I2CONCLR=1<<SIC_BIT;
 I2CONSET=1<<AA_BIT;
 while(((I2CONSET>>SI_BIT)&1)==0);
 I2CONCLR=1<<AAC_BIT;
 return I2DAT;
}
void i2c_restart()
{
 I2CONSET=1<<STA_BIT;
 I2CONCLR=1<<SIC_BIT;
 while(((I2CONSET>>SI_BIT)&1)==0);
 I2CONCLR=1<<STAC_BIT;
}

