#include "Main.h"
#include <stdio.h>
#include <stdint.h>
//#include "Functions.h"




/*
int simulate(uint32_t code){
  int OPCODE=code>>8;
  Opcode x;
  //x=opcodeTable[OPCODE](code);
	//int *simulator=&opcodeTable[OPCODE];
	//*simulator(code);
	printf("the address of WREG now is %#06x\n", &opcodeTable[OPCODE]);
	printf("the address of WREG now is %#06x\n", PICWREG);
	printf("the value of WREG now is %#06x\n",*PICWREG);
	printf("the value of code now is %#06x\n",code);
	printf("the value of opcode now is %#06x\n",OPCODE);



	return OPCODE;




}
Opcode opcodeTable[256]={
	//[0xaa]={addtest,0,0},
	//[0xbb]={minustest,0,0},
	[0x0E]={movlw},


};


  */




   /*
	*WREG=0x00FF;
	printf("the address of WREG now is %#06x\n", WREG);
	printf("the value of WREG now is %#06x\n",*WREG);

	*/


int movlw(uint32_t code){
  unsigned short data;
  data=code&0x00FF;
  *WREG=data;
  return 0;
}

int movwf(uint32_t code){
	int a=0x01&(code>>8);
	int address=code&0x00FF;
	return address;
}
