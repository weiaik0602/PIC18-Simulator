#ifndef _RAWFUNCTION_H
#define _RAWFUNCTION_H
#include <stdint.h>
//////////change value/////
void SET_PC(int newAddr);
void CLEAR_PC();
unsigned int GetA(uint8_t* code);
unsigned int GetD(uint8_t *code);
unsigned int GetB(uint8_t *code);
unsigned int GetAbsoluteAddress(int a,uint8_t address);
int GetValue(unsigned int address);
void rawCondBranch(int CondBit,int ExpectedBit,uint8_t *code);
void storeFileReg(int d,uint8_t value,uint16_t address);
char rawAdd(uint16_t v1,uint16_t v2,uint8_t CarryEnable);
void rawBitTestSkip(int xpectedBit,uint8_t *code);
void ClrStatus();
void SetZnN(uint8_t result);
void rawTblrd(uint32_t TBLPTR);
void rawTblwt(uint32_t TBLPTR);
void ClrTBLPTR();


#endif // _RAWFUNCTION_H
