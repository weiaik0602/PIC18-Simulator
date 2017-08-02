#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <stdint.h>


uint8_t PCL;
uint8_t PCLATH;
uint8_t PCLATU;

#define KB 1024
#define GET_PC()              (PCL|(PCLATH<<8)|(PCLATU<<16))
#define ADD_PC(step)          (SET_PC(GET_PC() + (step) * 2))


extern uint8_t memory[];
#define Status    ((StatusReg*)&memory[0xFD8])
#define WREG      (&memory[0xFE8])
#define BSR       (&memory[0xFE0])

#define C_Bit      0
#define OV_Bit     3
#define Z_Bit      2



typedef struct StatusReg StatusReg;
struct StatusReg{
  uint8_t C:1;
  uint8_t DC:1;
  uint8_t Z:1;
  uint8_t OV:1;
  uint8_t N:1;
};




  unsigned int Skip;


//get value
void SET_PC(int newAddr);
void CLEAR_PC();
unsigned int GetA(uint16_t code);
unsigned int GetD(uint16_t code);
unsigned int GetB(uint16_t code);
unsigned int ChangeAddressWithBSR(unsigned int address);
int GetValue(int a,unsigned int address);
void rawCondBranch(int CondBit,int ExpectedBit,uint16_t code);
void storeFileReg(int d,int a,uint8_t value,uint8_t address);
char rawAdd(uint16_t v1,uint16_t v2);
void rawBitTestSkip(int x,uint16_t code);
void ClrStatus();
//functions
void movlw(uint16_t code);
void movwf(uint16_t code);
void addwf(uint16_t code);
void movlb(uint16_t code);
void subwf(uint16_t code);
void bcf(uint16_t code);
void bsf(uint16_t code);
void setf(uint16_t code);
void clrf(uint16_t code);
void btfss(uint16_t code);
void btfsc(uint16_t code);
void nop(uint16_t code);
void movff(uint32_t code);
void bc(uint16_t code);
void bnc(uint16_t code);
void bnz(uint16_t code);
void bz(uint16_t code);
void bov(uint16_t code);
void bnov(uint16_t code);
void addwfc(uint16_t code);
void andwf(uint16_t code);
//display

void ShowWREG();
void ShowBSR();
void ShowMemory(unsigned address);
void ShowPC();
void ShowStatus();



/*
'body':
  'ctrl-shift-s': 'window:save-all'
*/

#endif // _SIMULATOR_H
