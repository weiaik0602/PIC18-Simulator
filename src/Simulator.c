#include "Simulator.h"
#include "GlobalVariable.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>






Simulator OpcodeTable[256]={
	[0x00]={zero},
  [0x24]={addwf},
  [0x25]={addwf},
  [0x26]={addwf},
  [0x27]={addwf},
  [0x20]={addwfc},
  [0x21]={addwfc},
  [0x22]={addwfc},
  [0x23]={addwfc},
  [0x14]={andwf},
  [0x16]={andwf},
  [0x15]={andwf},
  [0x17]={andwf},
  [0x6B]={clrf},
  [0x6A]={clrf},
/*  [0x1C]={comf},
  [0x1D]={comf},
  [0x1E]={comf},
  [0x1F]={comf},
  [0x62]={cpfseq},
  [0x63]={cpfseq},
  [0x64]={cpfsgt},
  [0x65]={cpfsgt},
  [0x60]={cpfslt},
  [0x61]={cpfslt},
  [0x04]={decf},
  [0x05]={decf},
  [0x06]={decf},
  [0x07]={decf},
  [0x2C]={decfsz},
  [0x2D]={decfsz},
  [0x2E]={decfsz},
  [0x2F]={decfsz},
  [0x4C]={dcfsnz},
  [0x4D]={dcfsnz},
  [0x4E]={dcfsnz},
  [0x4F]={dcfsnz},
  [0x28]={incf},
  [0x29]={incf},
  [0x2A]={incf},
  [0x2B]={incf},
  [0x3C]={incfsz},
  [0x3D]={incfsz},
  [0x3E]={incfsz},
  [0x3F]={incfsz},
  [0x48]={infsnz},
  [0x49]={infsnz},
  [0x4A]={infsnz},
  [0x4B]={infsnz},*/
  [0x10]={iorwf},
  [0x11]={iorwf},
  [0x12]={iorwf},
  [0x13]={iorwf},
/*  [0x50]={movf},
  [0x51]={movf},
  [0x52]={movf},
  [0x53]={movf},*/
  [0x6E]={movwf},
  [0x6F]={movwf},
/*  [0x02]={mulwf},
  [0x03]={mulwf},
  [0x6C]={negf},
  [0x6D]={negf},
  [0x34]={rlcf},
  [0x35]={rlcf},
  [0x36]={rlcf},
  [0x37]={rlcf},
  [0x44]={rlncf},
  [0x45]={rlncf},
  [0x46]={rlncf},
  [0x47]={rlncf},
  [0x30]={rrcf},
  [0x31]={rrcf},
  [0x32]={rrcf},
  [0x33]={rrcf},
  [0x40]={rrncf},
  [0x41]={rrncf},
  [0x42]={rrncf},
  [0x43]={rrncf},*/
  [0x68]={setf},
  [0x69]={setf},
/*  [0x54]={subfwb},
  [0x55]={subfwb},
  [0x56]={subfwb},
  [0x57]={subfwb},*/
  [0x5C]={subwf},
  [0x5D]={subwf},
  [0x5E]={subwf},
  [0x5F]={subwf},/*
  [0x58]={subwfb},
  [0x59]={subwfb},
  [0x5A]={subwfb},
  [0x5B]={subwfb},
  [0x38]={swapf},
  [0x39]={swapf},
  [0x3A]={swapf},
  [0x3B]={swapf},
  [0x67]={tstfsz2},
  [0x68]={tstfsz},
  [0x18]={xorwf},
  [0x19]={xorwf},
  [0x1A]={xorwf},
  [0x1B]={xorwf},*/
  [0x90]={bcf},
  [0x91]={bcf},
  [0x92]={bcf},
  [0x93]={bcf},
  [0x94]={bcf},
  [0x95]={bcf},
  [0x96]={bcf},
  [0x97]={bcf},
  [0x98]={bcf},
  [0x99]={bcf},
  [0x9A]={bcf},
  [0x9B]={bcf},
  [0x9C]={bcf},
  [0x9D]={bcf},
  [0x9E]={bcf},
  [0x9F]={bcf},
  [0x80]={bsf},
  [0x81]={bsf},
  [0x82]={bsf},
  [0x83]={bsf},
  [0x84]={bsf},
  [0x85]={bsf},
  [0x86]={bsf},
  [0x87]={bsf},
  [0x88]={bsf},
  [0x89]={bsf},
  [0x8A]={bsf},
  [0x8B]={bsf},
  [0x8C]={bsf},
  [0x8D]={bsf},
  [0x8E]={bsf},
  [0x8F]={bsf},
  [0xB0]={btfsc},
  [0xB1]={btfsc},
  [0xB2]={btfsc},
  [0xB3]={btfsc},
  [0xB4]={btfsc},
  [0xB5]={btfsc},
  [0xB6]={btfsc},
  [0xB7]={btfsc},
  [0xB8]={btfsc},
  [0xB9]={btfsc},
  [0xBA]={btfsc},
  [0xBB]={btfsc},
  [0xBC]={btfsc},
  [0xBD]={btfsc},
  [0xBE]={btfsc},
  [0xBF]={btfsc},
  [0xA0]={btfss},
  [0xA1]={btfss},
  [0xA2]={btfss},
  [0xA3]={btfss},
  [0xA4]={btfss},
  [0xA5]={btfss},
  [0xA6]={btfss},
  [0xA7]={btfss},
  [0xA8]={btfss},
  [0xA9]={btfss},
  [0xAA]={btfss},
  [0xAB]={btfss},
  [0xAC]={btfss},
  [0xAD]={btfss},
  [0xAE]={btfss},
  [0xAF]={btfss},/*
  [0x70]={btg},
  [0x71]={btg},
  [0x72]={btg},
  [0x73]={btg},
  [0x74]={btg},
  [0x75]={btg},
  [0x76]={btg},
  [0x77]={btg},
  [0x78]={btg},
  [0x79]={btg},
  [0x7A]={btg},
  [0x7B]={btg},
  [0x7C]={btg},
  [0x7D]={btg},
  [0x7E]={btg},
  [0x7F]={btg},*/
  [0xE1]={bnz},
  [0xE2]={bc},
  [0xE3]={bnc},
  [0xE4]={bov},
  [0xE5]={bnov},/*
  [0xE6]={bn},
  [0xE7]={bnn},
  [0x08]={sublw},
  [0x09]={iorlw},
  [0x0A]={xorlw},
  [0x0B]={andlw},
  [0x0C]={retlw},
  [0x0D]={mullw},

  [0x0F]={addlw},
  [0x01]={movlb},*/
	 [0x0E]={movlw},
  [0xF0]={nop},
  [0xF1]={nop},
  [0xF2]={nop},
  [0xF3]={nop},
  [0xF4]={nop},
  [0xF5]={nop},
  [0xF6]={nop},
  [0xF7]={nop},
  [0xF8]={nop},
  [0xF9]={nop},
  [0xFA]={nop},
  [0xFC]={nop},
  [0xFD]={nop},
  [0xFE]={nop},
  [0xFF]={nop},/*
  [0xEC]={call},
  [0xED]={call},
  [0xEF]={goto1},
  [0xEE]={lfsr},
  [0xD8]={rcall},
  [0xD9]={rcall},
  [0xDA]={rcall},
  [0xDB]={rcall},
  [0xDC]={rcall},
  [0xDD]={rcall},
  [0xDE]={rcall},
  [0xDF]={rcall},*/
  [0xC0]={movff},
  [0xC1]={movff},
  [0xC2]={movff},
  [0xC3]={movff},
  [0xC4]={movff},
  [0xC5]={movff},
  [0xC6]={movff},
  [0xC7]={movff},
  [0xC8]={movff},
  [0xC9]={movff},
  [0xCA]={movff},
  [0xCB]={movff},
  [0xCC]={movff},
  [0xCD]={movff},
  [0xCE]={movff},
  [0xCF]={movff},
	[0xD0]={bra},
	[0xD1]={bra},
	[0xD2]={bra},
	[0xD3]={bra},
	[0xD4]={bra},
	[0xD5]={bra},
	[0xD6]={bra},
	[0xD7]={bra},
};

void zero(uint8_t *code){
	uint8_t next_instruction=*(code+1);
	switch(next_instruction){
		case(0x08):tblrd();
							break;
		case(0x09):tblrdposi();
							break;
		case(0x0A):tblrdposd();
							break;
		case(0x0B):tblrdprei();
							break;
		case(0x0C):tblwt();
							break;
		case(0x0D):tblwtposi();
							break;
		case(0x0E):tblwtposd();
							break;
		case(0x0F):tblwtprei();
							break;
			default:nop(code);
	};
}

void Simulate(int size){
  int i=0;
   while(i<size){
     OpcodeTable[flash[i]].execute(&flash[i]);
     i=GET_PC();
   }
}




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

/////////////////////////////////////////////////////////////////////////////
//functions

void movlb(uint8_t *code){
	storeFileReg(1,*(code+1)&0xF,BSR);
	ADD_PC(1);
}
void movlw(uint8_t *code){
	storeFileReg(1,*(code+1),WREG);
	ADD_PC(1);
}
void movwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t value=GetValue(WREG);
	storeFileReg(1,value,address);
	ADD_PC(1);
}
void addwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int v2=GetValue(WREG);
	realresult=rawAdd(v1,v2,0);
	storeFileReg(d,realresult,address);
	ADD_PC(1);
}
void subwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int v2=GetValue(WREG);
	realresult=rawAdd(v1,-v2,0);
	storeFileReg(d,realresult,address);
	ADD_PC(1);
}
void bcf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t reset=~(0x01<<b);
	int v1=GetValue(address);
	storeFileReg(1,(v1&reset),address);
	ADD_PC(1);
}
void bsf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t reset=(0x01<<b);
	int v1=GetValue(address);
	storeFileReg(1,(v1|reset),address);
	ADD_PC(1);
}
void setf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	storeFileReg(1,0xFF,address);
	ADD_PC(1);
}
void clrf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	storeFileReg(1,0x00,address);
	STATUS->Z=1;
	ADD_PC(1);
}
void btfss(uint8_t *code){
	rawBitTestSkip(SET,code);
}
void btfsc(uint8_t *code){
	rawBitTestSkip(CLEAR,code);
}
void nop(uint8_t *code){
	ADD_PC(1);
}
void movff(uint8_t *code){
	unsigned int source=(*(code)&0xF)<<8|*(code+1);
	unsigned int destination=(*(code+2)&0xF)<<8|*(code+3);
	memory[destination]=memory[source];
	ADD_PC(2);
}
void bc(uint8_t *code){
  rawCondBranch(C_Bit,1,code);
}
void bnc(uint8_t *code){
	rawCondBranch(C_Bit,0,code);
}
void bz(uint8_t *code){
	rawCondBranch(Z_Bit,1,code);
}
void bnz(uint8_t *code){
	rawCondBranch(Z_Bit,0,code);
}
void bov(uint8_t *code){
	rawCondBranch(OV_Bit,1,code);
}
void bnov(uint8_t *code){
		rawCondBranch(OV_Bit,0,code);
}
void addwfc(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int v2=GetValue(WREG);
	realresult=rawAdd(v1,v2,1);
	storeFileReg(d,realresult,address);
	ADD_PC(1);
}
void andwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	unsigned int result;
	uint8_t realresult;

	int v1=GetValue(address);
	int v2=GetValue(WREG);
	result=v2&v1;
	realresult=result&0xFF;

	storeFileReg(d,realresult,address);
	SetZnN(realresult);
	ADD_PC(1);
}
void comf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t value=GetValue(address);
	value=~value;
	storeFileReg(d,value,address);
	SetZnN(value);
	ADD_PC(1);
}
void iorwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t value=GetValue(address);
	value=value|GetValue(WREG);
	storeFileReg(d,value,address);
	SetZnN(value);
	ADD_PC(1);
}
void bra(uint8_t *code){
	uint16_t step=((*code)&0x07)<<8|*(code+1);
	if(step<0x400)
	 	ADD_PC(step);
	else
		ADD_PC(-(0x800-step));

	ADD_PC(1);
}
void tblrd(){
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblrd(TBLPTR);
}
void tblrdposi(){
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblrd(TBLPTR);
	TBLPTRL+=1;
}
void tblrdposd(){
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblrd(TBLPTR);
	TBLPTRL-=1;
}
void tblrdprei(){
	TBLPTRL+=1;
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblrd(TBLPTR);
}
void tblwt(){
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblwt(TBLPTR);
}
void tblwtposi(){
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblwt(TBLPTR);
	TBLPTRL+=1;
}
void tblwtposd(){
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblwt(TBLPTR);
	TBLPTRL-=1;
}
void tblwtprei(){
	TBLPTRL+=1;
	uint32_t TBLPTR=GET_TBLPTR();
	rawTblwt(TBLPTR);
}
