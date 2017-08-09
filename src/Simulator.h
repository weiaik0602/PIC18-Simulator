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

void Simulate(uint8_t *opcode);



//get value
void SET_PC(int newAddr);
void CLEAR_PC();
unsigned int GetA(uint8_t* code);
unsigned int GetD(uint8_t *code);
unsigned int GetB(uint8_t *code);
unsigned int ChangeAddressWithBSR(unsigned int address);
int GetValue(int a,unsigned int address);
void rawCondBranch(int CondBit,int ExpectedBit,uint8_t *code);
void storeFileReg(int d,int a,uint8_t value,uint8_t address);
char rawAdd(uint16_t v1,uint16_t v2,uint8_t CarryEnable);
void rawBitTestSkip(int x,uint8_t *code);
void ClrStatus();
void SetZnN(uint8_t result);
//functions
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

//display

void ShowWREG();
void ShowBSR();
void ShowMemory(unsigned address);
void ShowPC();
void ShowStatus();




#endif // _SIMULATOR_H
