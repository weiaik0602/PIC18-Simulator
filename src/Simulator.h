#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include <stdint.h>



  #define KB 1024
	//char code[8*KB];
	uint8_t memory[32*KB];
	static uint8_t *WREG=&memory[0xFE8];
	static uint8_t *BSR=&memory[0xFE0];


  unsigned int Caddress;
  unsigned int PC;
  unsigned int Skip;
  unsigned int C;
  unsigned int DC;
  unsigned int Z;
  unsigned int OV;
  unsigned int N;
//get value
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