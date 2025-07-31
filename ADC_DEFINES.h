#define FOSC 12000000
#define CCLK (5*FOSC)
#define pclk (CCLK/4)
#define ADC_CLK 3000000
#define CLKDIV_BITS 8 //8 to 15
#define CLKDIV ((pclk/ADC_CLK)-1)
#define PDN 21
#define CHSEL_BITS 0 //0 to7
#define STARTBIT 24
#define DIGDATA 6 //6 to 15
#define DONEBIT 31