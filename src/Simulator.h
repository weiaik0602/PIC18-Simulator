#ifndef _SIMULATOR_H
#define _SIMULATOR_H
#include <stdint.h>




typedef struct Simulator Simulator;
struct StatusReg{
  uint8_t C:1;
  uint8_t DC:1;
  uint8_t Z:1;
  uint8_t OV:1;
  uint8_t N:1;
};
struct Simulator{
  void (*execute)(uint8_t *code);    // a function
};




void Simulate(int size);
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


//functions
void zero(uint8_t *code);
void movlb(uint8_t *code);
void movlw(uint8_t *code);
void movwf(uint8_t *code);
void addwf(uint8_t *code);
void subwf(uint8_t *code);
void bcf(uint8_t *code);
void bsf(uint8_t *code);
void setf(uint8_t *code);
void clrf(uint8_t *code);
void btfss(uint8_t *code);
void btfsc(uint8_t *code);
void nop(uint8_t *code);
void movff(uint8_t *code);
void bc(uint8_t *code);
void bnc(uint8_t *code);
void bnz(uint8_t *code);
void bz(uint8_t *code);
void bov(uint8_t *code);
void bnov(uint8_t *code);
void addwfc(uint8_t *code);
void andwf(uint8_t *code);
void comf(uint8_t *code);
void iorwf(uint8_t *code);
void tblrd();
void tblrdposi();
void tblrdposd();
void tblrdprei();
void tblwt();
void tblwtposi();
void tblwtposd();
void tblwtprei();
void bra(uint8_t *code);



#endif // _SIMULATOR_H
