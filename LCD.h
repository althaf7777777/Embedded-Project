#include"types.h"
void CmdLCD(u8 cmd);
void CharLCD(u8 ascii);
void WriteLCD(u8 cmd);
void InitLCD(void);
void StrLCD(s8 *);
void U32LCD(u32);
void S32LCD(s32);
void F32LCD(f32, u8);
void BuildCGRAM(s8 *, u8);