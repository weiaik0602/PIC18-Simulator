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
	if(Skip==1){
		Skip=0;
	}
	else{
  unsigned short data;
  data=code&0x00FF;
  *WREG=data;
	}
	PC+=2;
	Caddress+=2;
}
void movwf(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
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
	PC+=2;
	Caddress+=2;
}
void addwf(uint16_t code){
	if(Skip==1){
			Skip=0;
	}
	else{
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=code&0x00FF;
	unsigned int result;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		if(d==0){
			result=*WREG+*FileRegister;
			*WREG=result;
			if(result>0xFF){
				C=1;
			}
		}
		else{
			result=*WREG+*FileRegister;
			*FileRegister=result;
			if(result>0xFF){
				C=1;
			}
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
	PC+=2;
	Caddress+=2;
}
void movlb(uint16_t code){
	if(Skip==1){
			Skip=0;
	}
	else{
	*BSR=code&0x000F;
	}
	PC+=2;
	Caddress+=2;
}
void subwf(uint16_t code){
	if(Skip==1){
			Skip=0;
	}
	else{
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=code&0x00FF;
	int result;
	uint8_t *FileRegister;

	if(a==0){
		FileRegister=&memory[address];
		if(d==0){
			result=*FileRegister-*WREG;
			*WREG=result;
			if(result>=0x00)
				C=1;
			if(result<0x00){
				N=1;
				C=0;
			}
		}
		else{
			result=*FileRegister-*WREG;
			*FileRegister=result;
			if(result>=0x00)
				C=1;
			if(result<0x00){
				N=1;
				C=0;
			}
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
	PC+=2;
	Caddress+=2;
}
void bcf(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
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
	PC+=1;
}
void bsf(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
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
	PC+=2;
	Caddress+=2;
}
void setf(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
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
	PC+=2;
	Caddress+=2;
}
void clrf(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
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
	PC+=2;
	Caddress+=2;
}
void btfss(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=code&0x00FF;
	//uint8_t reset=(0x01<<b);
	uint8_t *FileRegister;
	if(a==0){
		FileRegister=&memory[address];
		unsigned int bit=(*FileRegister>>b)&0x01;
		if(bit==1){
			Skip=1;
		}
	}
	else{
		FileRegister=&memory[address];
		unsigned int bit=(*FileRegister>>b)&0x01;
		if(bit==1){
			Skip=1;
			}
	}
	PC+=2;
	Caddress+=2;
	}
}
void btfsc(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=code&0x00FF;
	//uint8_t reset=(0x01<<b);
	uint8_t *FileRegister;
	if(a==0){
		FileRegister=&memory[address];
		unsigned int bit=(*FileRegister>>b)&0x01;
		if(bit==0){
			Skip=1;
		}
	}
	else{
		FileRegister=&memory[address];
		unsigned int bit=(*FileRegister>>b)&0x01;
		if(bit==0){
			Skip=1;
			}
	}
	PC+=2;
	Caddress+=2;
	}
}
void nop(){
	PC+=2;
	Caddress+=2;
}
void movff(uint32_t code){
	if(Skip==1){
		Skip=0;
		}
	else{
	unsigned int destination=code&0xFFF;
	unsigned int source=(code>>16)&0xFFF;
	memory[destination]=memory[source];
	}
	PC+=4;
	Caddress+=4;
}
///////////////////////////////////////////////////////////////////////////
//display
void ShowWREG(){
	printf("the value of WREG now is %#04x\n",*WREG);
}
void ShowBSR(){
	printf("the value of BSR now is %#04x\n",*BSR);
}
void ShowMemory(unsigned int address){
	printf("the value of %#04x now is %#04x\n",address,memory[address]);
}
void ShowPC(){
	printf("the value of PC now is %d\n",PC);
}
void ShowC(){
	printf("the value of C now is %d\n",C);
}
void ShowN(){
	printf("the value of N now is %d\n",N);
}
