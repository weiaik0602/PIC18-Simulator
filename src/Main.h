#ifndef _MAIN_H
#define _MAIN_H
#include <stdint.h>
//#include "Functions.h"


  #define KB 1024
	char code[8*KB];
	uint8_t memory[32*KB];
	static uint8_t *WREG=&memory[0xFE8];
	static uint8_t *BSR=&memory[0xFE0];
	//*BSR=0;
/*
typedef struct Opcode Opcode;
struct Opcode{
  int (*execute)(uint32_t *code);
 // int d;
 // int a;
};


int simulate(uint32_t code);
Opcode opcodeTable[256];
*/




int movlw(uint16_t code);
int movwf(uint16_t code);



#endif // _MAIN_H
