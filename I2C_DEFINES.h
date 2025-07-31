#include<lpc21xx.h>
#include"types.h"
#define I2C_SPEED 100000
#define FOSC 12000000
#define CCLK (5*FOSC)
//#define PCLK (CCLK/4)
#define BITRATE ((PCLK/I2C_SPEED)/2)
#define I2EN_BIT 6
#define STA_BIT 5
#define STO_BIT 4
#define STAC_BIT 4
#define I2_SIC 3
#define SI_BIT 3
#define AA_BIT 2
#define AAC_BIT 2
#define I2_EN_CLR 5
