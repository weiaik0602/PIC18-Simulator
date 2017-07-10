#include "Main.h"
#include <stdio.h>
#include <stdint.h>


/////////////////////////////////////////////////////////////////////////////
//get value

unsigned int GetA(uint16_t code){
	return 0x01&(code>>8);
}
unsigned int GetD(uint16_t code){
	return 0x01&(code>>9);
}
unsigned int ChangeAddressWithBSR(unsigned int address){
	unsigned int vBSR=*BSR;
	vBSR=vBSR<<8;
	address=address|vBSR;
	return address;
}
unsigned int GetB(uint16_t code){
	return (code>>9)&0x0007;
}
/////////////////////////////////////////////////////////////////////////////
//functions
void movlw(uint16_t code){
  unsigned short data;
  data=code&0x00FF;
  *WREG=data;
}
void movwf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int address=code&0x00FF;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		*FileRegister=*WREG;
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		*FileRegister=*WREG;
	}

}
void addwf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=code&0x00FF;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		if(d==0){
			*WREG=*WREG+*FileRegister;
		}
		else{
			*FileRegister=*FileRegister+*WREG;
		}
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		if(d==0){
			*WREG=*WREG+*FileRegister;
		}
		else{
			*FileRegister=*FileRegister+*WREG;
		}
	}
}
void movlb(uint16_t code){
	*BSR=code&0x000F;
}
void subwf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=code&0x00FF;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		if(d==0){
			*WREG=*FileRegister-*WREG;
		}
		else{
			*FileRegister=*FileRegister-*WREG;
		}
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		if(d==0){
			*WREG=*FileRegister-*WREG;
		}
		else{
			*FileRegister=*FileRegister-*WREG;
		}
	}
}
void bcf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=code&0x00FF;
	uint8_t reset=~(0x01<<b);
	uint8_t *FileRegister;
	if(a==0){
		FileRegister=&memory[address];
		*FileRegister=(*FileRegister&reset);
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		*FileRegister=(*FileRegister&reset);
	}
}
void bsf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=code&0x00FF;
	uint8_t reset=(0x01<<b);
	uint8_t *FileRegister;
	if(a==0){
		FileRegister=&memory[address];
		*FileRegister=(*FileRegister|reset);
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		*FileRegister=(*FileRegister|reset);
	}
}
void setf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int address=code&0x00FF;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		*FileRegister=*FileRegister|0xFF;
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		*FileRegister=*FileRegister|0xFF;
	}
}
void clrf(uint16_t code){
	unsigned int a=GetA(code);
	unsigned int address=code&0x00FF;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		*FileRegister=*FileRegister&0x00;
	}
	else{
		address=ChangeAddressWithBSR(address);
		FileRegister=&memory[address];
		*FileRegister=*FileRegister&0x00;
	}
}
///////////////////////////////////////////////////////////////////////////
//display
void ShowValue(){
	printf("the value of WREG now is %#04x\n",*WREG);
	printf("the value of BSR now is %#04x\n",*BSR);
	printf("the value of 0x59E now is %#04x\n",memory[0x59E]);

}
void ShowWREG(){
	printf("the value of WREG now is %#04x\n",*WREG);
}
void ShowBSR(){
	printf("the value of BSR now is %#04x\n",*BSR);
}
void ShowMemory(unsigned int address){
	printf("the value of %#04x now is %#04x\n",address,memory[address]);
}
