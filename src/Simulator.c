#include "Simulator.h"
#include <stdio.h>
#include <stdint.h>

uint8_t memory[32*KB];




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

void SET_PC(int newAddr){
	PCL=newAddr&0xFF;
  PCLATH=(newAddr>>8)&0xFF;
  PCLATU=(newAddr>>16)&0xFF;
}
void CLEAR_PC(){
	PCL=0;
  PCLATH=0;
  PCLATU=0;
}
void storeFileReg(int d,int a,uint8_t value,uint8_t address){
	uint8_t *FileRegister;
	unsigned int newaddress;
	if(d==0)
			*WREG=value;
	else{
		if(a==0){
		FileRegister=&memory[address];
		*FileRegister=value;
		}
		else{
			newaddress=ChangeAddressWithBSR(address);
			FileRegister=&memory[newaddress];
			*FileRegister=value;
		}
	}
}

int GetValue(int a,unsigned int address){
	unsigned int newaddress;
	if(a==0)
		return memory[address];
	else{
		newaddress=ChangeAddressWithBSR(address);
		return memory[newaddress];
	}
}
void rawCondBranch(int CondBit,int ExpectedBit,uint16_t code){
  if(Skip==1){
    Skip=0;
  }
  else{
		unsigned int Bit=(memory[0xFD8]<<CondBit)&0x01;
    if(Bit==ExpectedBit){
      char step=code&0xFF;
      if(step<0){
        step=~(step);
        ADD_PC(-step);
      }
      else
      ADD_PC(step+1);
    }
		else
		ADD_PC(1);
  }
}
int rawAdd(int v1,int v2){
	return (v1)+(v2);
}
void rawBitTestSkip(int x,uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
		unsigned int a=GetA(code);
		unsigned int b=GetB(code);
		unsigned int address=code&0x00FF;
		uint8_t *FileRegister;
		if(a==0){
			FileRegister=&memory[address];
			unsigned int bit=(*FileRegister>>b)&0x01;
			if(bit==x){
				Skip=1;
				}
			}
		else{
			address=ChangeAddressWithBSR(address);
			FileRegister=&memory[address];
			unsigned int bit=(*FileRegister>>b)&0x01;
			if(bit==x){
			Skip=1;
			}
			}
	ADD_PC(1);
	}
}


/////////////////////////////////////////////////////////////////////////////
//functions

void movlb(uint16_t code){
	if(Skip==1){
			Skip=0;
	}
	else{
	*BSR=code&0x000F;
	}
	ADD_PC(1);
}
void movlw(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	else{
  unsigned short data;
  data=code&0x00FF;
  *WREG=data;
	}
	ADD_PC(1);

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
	ADD_PC(1);

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

	int v1=GetValue(a,address);
	int v2=*WREG;
	result=rawAdd(v1,v2);
	storeFileReg(d,a,result,address);
	if(result>0x100){
		Status->C=1;
	}
	}
	ADD_PC(1);
}
void subwf(uint16_t code){
	if(Skip==1){
			Skip=0;
	}
	else{
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=code&0x00FF;
	unsigned int result;
	uint8_t *FileRegister;

	int v1=GetValue(a,address);
	int v2=*WREG;
	result=rawAdd(v1,-v2);
	storeFileReg(d,a,result,address);
	if(result>0xFF){
		Status->N=1;
	}
	}
	ADD_PC(1);
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
	ADD_PC(1);
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
	ADD_PC(1);
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
	ADD_PC(1);
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
	ADD_PC(1);
}
void btfss(uint16_t code){
	rawBitTestSkip(1,code);
}
void btfsc(uint16_t code){
	rawBitTestSkip(0,code);
}
void nop(uint16_t code){
	if(Skip==1){
		Skip=0;
	}
	ADD_PC(1);
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
	ADD_PC(2);
}
void bc(uint16_t code){
  rawCondBranch(C_Bit,1,code);
}
void bnc(uint16_t code){
	rawCondBranch(C_Bit,0,code);
}
void bz(uint16_t code){
	rawCondBranch(Z_Bit,1,code);
}
void bnz(uint16_t code){
	rawCondBranch(Z_Bit,0,code);
}
void bov(uint16_t code){
	rawCondBranch(OV_Bit,1,code);
}
void bnov(uint16_t code){
		rawCondBranch(OV_Bit,0,code);
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
	printf("the value of PC now is %#04x\n",GET_PC());
}
void ShowC(){
	printf("the value of C now is %d\n",Status->C);
}
void ShowN(){
	printf("the value of N now is %d\n",Status->N);
}
void ShowStatus(){
	printf("%#04x\n",*Status );
}
