#ifndef _MAIN_H
#define _MAIN_H
#include <stdint.h>
//#include "Functions.h"


  #define KB 1024
	//char code[8*KB];
	uint8_t memory[32*KB];
	static uint8_t *WREG=&memory[0xFE8];
	static uint8_t *BSR=&memory[0xFE0];

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
void


//display
void ShowValue();
void ShowWREG();
void ShowBSR();
void ShowMemory(unsigned address);
#endif // _MAIN_H
