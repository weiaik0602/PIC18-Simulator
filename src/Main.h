#ifndef _MAIN_H
#define _MAIN_H
#include <stdint.h>
//#include "Functions.h"


  #define KB 1024
	char code[8*KB];
	volatile char memory[32*KB];
	static uint32_t *WREG=&memory[0xFE8];

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




int movlw(uint32_t code);
int movwf(uint32_t code);



#endif // _MAIN_H
