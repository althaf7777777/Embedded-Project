#include"types.h"
typedef struct CAN_FRAME
{
 u32 ID;
 struct bitfield
 {
  u32 RTR:1;
  u32 DLC:4;
 }bfv;
 u32 data1, data2;
}CANF;
void init_CAN1(void);
void CAN1_tx(CANF txf);
void CAN1_rx(CANF *rxf);