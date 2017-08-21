#include <stdint.h>
#include "Function.h"
#include "RawFunction.h"
#include "GlobalVariable.h"


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
