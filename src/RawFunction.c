#include "RawFunction.h"
#include "GlobalVariable.h"
#include <stdint.h>

////////////////////change value////////////////////////////////////////////////////
unsigned int GetA(uint8_t* code){
	return 0x01&(*code);
}
unsigned int GetD(uint8_t *code){
	return 0x01&(*code>>1);
}
unsigned int GetB(uint8_t *code){
	return (*code>>1)&0x0007;
}
unsigned int GetAbsoluteAddress(int a,uint8_t address){
	unsigned int vBSR=memory[BSR];
	uint16_t newaddress;
	vBSR=vBSR<<8;
	if(a==1)
		newaddress=address|vBSR;
	else{
		if(address>0x7F)
			newaddress=0xF00|address;
		else
			newaddress=address;
		}
	return newaddress;
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
void storeFileReg(int d,uint8_t value,uint16_t address){
	if(address>0xF79){
		if(address==EECON2){
			if(memory[EECON2]==0x55 &&value==0xAA)
				enableFlashWrite=1;
			}
		}
	if(d==0)
			memory[WREG]=value;
	else
		memory[address]=value;
}
int GetValue(unsigned int address){
		return memory[address];
}
char rawAdd(uint16_t v1,uint16_t v2,uint8_t CarryEnable){
	uint16_t result;
	uint8_t realresult;
	uint16_t decimalresult;
	if(CarryEnable==1)
		STATUS->C=STATUS->C;
	else
		STATUS->C=0;
	result= (v1)+(v2)+STATUS->C;
	decimalresult=(v1&0xF)+(v2&0xF)+STATUS->C;
	realresult=result&0xFF;
	if(decimalresult>0xF)
		STATUS->DC=1;
	else
		STATUS->DC=0;
	if(result>0xFF)
		STATUS->C=1;
	else
		STATUS->C=0;
	if(realresult==0)
		STATUS->Z=1;
	else
		STATUS->Z=0;
	if(realresult>0x79)   //0x80 to 0xFF is negative num
		STATUS->N=1;
	else
		STATUS->N=0;
	STATUS->OV=0;
	if(v1<0x80&&v2<0x80&&realresult>0x79)   //v1(pos)+v2(pos)=neg
		STATUS->OV=1;
	if(v1>0x79&&v2>0x79&&realresult<0x80)   //v1(neg)+v2(neg)=pos
		STATUS->OV=1;
	return realresult;
}
void ClrStatus(){
	memory[0xFD8]=0;
}
void SetZnN(uint8_t value){
	if(value>0x79)
		STATUS->N=1;
	else
		STATUS->N=0;
	if(value==0)
		STATUS->Z=1;
	else
		STATUS->Z=0;
}
void rawBitTestSkip(int xpectedBit,uint8_t *code){
		unsigned int a=GetA(code);
		unsigned int b=GetB(code);
		unsigned int address=*(code+1);
		address=GetAbsoluteAddress(a,address);
		uint8_t value=GetValue(address);
		unsigned int bit=(value>>b)&0x01;
		if(bit==xpectedBit)
			ADD_PC(2);
		else
			ADD_PC(1);
}
void rawCondBranch(int CondBit,int ExpectedBit,uint8_t *code){
		unsigned int Bit=(memory[0xFD8]>>CondBit)&0x01;
    if(Bit==ExpectedBit){
      char step=*(code+1);
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
void ClrTBLPTR(){
	TBLPTRL=0;
	TBLPTRH=0;
	TBLPTRU=0;
}
void rawTblrd(uint32_t TBLPTR){
	uint32_t temp;
	if(TBLPTR%2==0){
		temp=TBLPTR+1;
	}
	else{
		temp=TBLPTR-1;
	}
	storeFileReg(1,flash[temp],TABLAT);
	ADD_PC(1);
}
void rawTblwt(uint32_t TBLPTR){
	if(enableFlashWrite==1){
		uint32_t TBptr=TBLPTR;
		while(TBptr>7){
			TBptr-=8;
		}
	tableBuffer[TBptr]=memory[TABLAT];
	}
	ADD_PC(1);
}
