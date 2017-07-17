#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <stdint.h>


uint8_t PCL;
uint8_t PCLATH;
uint8_t PCLATU;

#define KB 1024
#define GET_PC()              (PCL|(PCLATH<<8)|(PCLATU<<16))

#define ADD_PC(step)          (SET_PC(GET_PC() + (step) * 2))









typedef struct StatusReg StatusReg;
struct StatusReg{
  uint8_t C:1;
  uint8_t DC:1;
  uint8_t Z:1;
  uint8_t OV:1;
  uint8_t N:1;
};

StatusReg Status;

	//char code[8*KB];
	uint8_t memory[32*KB];
	static uint8_t *WREG=&memory[0xFE8];
	static uint8_t *BSR=&memory[0xFE0];




  //unsigned int Caddress;
  //unsigned int PC;
  unsigned int Skip;


//get value
void SET_PC(int newAddr);
unsigned int GetA(uint16_t code);
unsigned int GetD(uint16_t code);
unsigned int ChangeAddressWithBSR(unsigned int address);
unsigned int GetB(uint16_t code);

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
void nop();
void movff(uint32_t code);
void bc(uint16_t code);
void bnc(uint16_t code);
void bnz(uint16_t code);
void bz(uint16_t code);
void bov(uint16_t code);
void bnov(uint16_t code);

//display

void ShowWREG();
void ShowBSR();
void ShowMemory(unsigned address);
void ShowPC();




/*
'body':
  'ctrl-shift-s': 'window:save-all'
*/

#endif // _SIMULATOR_H
