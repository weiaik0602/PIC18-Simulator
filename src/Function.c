#include <stdint.h>
#include "Function.h"
#include "RawFunction.h"
#include "GlobalVariable.h"


/////////////////////////////////////////////////////////////////////////////
//functions
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
void daw(){
	uint8_t value=GetValue(WREG);
	uint8_t v30=(value&0x0F);
	uint8_t v74=(value&0xF0)>>4;
	if(v30>9||STATUS->DC==1)
		v30=v30+6;
	else
		v30=v30;
	if(v74>9||STATUS->C==1)
		v74=v74+6;
	else
		v74=v74;
	memory[WREG]=(v74<<4)|v30;
}
void movlb(uint8_t *code){
	storeFileReg(1,*(code+1)&0xF,BSR);
	ADD_PC(1);
}
void movlw(uint8_t *code){
	storeFileReg(0,*(code+1),WREG);
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
	if(realresult<0x80)
		STATUS->C=1;
	else
		STATUS->C=0;
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
void btg(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int b=GetB(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t value=GetValue(address);
	char bit=(value>>b)&0x01;
	bit=(~bit)|0xFE;
	bit=bit<<b;
	uint8_t mask=~(0x01<<b);
	bit=bit|mask;
	value=value&bit;
	storeFileReg(1,value,address);
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
void bn(uint8_t *code){
  rawCondBranch(N_Bit,1,code);
}
void bnn(uint8_t *code){
	rawCondBranch(N_Bit,0,code);
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
void cpfseq(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	int v2=memory[WREG];
	if(v1==v2)
		ADD_PC(2);
	else
		ADD_PC(1);
}
void cpfsgt(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	int v2=memory[WREG];
	if(v1>v2)
		ADD_PC(2);
	else
		ADD_PC(1);
}
void cpfslt(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	int v2=memory[WREG];
	if(v1<v2)
		ADD_PC(2);
	else
		ADD_PC(1);
}
void decf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int v2=-1;
	realresult=rawAdd(v1,v2,0);
	storeFileReg(d,realresult,address);
	ADD_PC(1);
}
void decfsz(uint8_t *code){
	int result=rawDecOrInc(code,-1);
	if(result==0)
	ADD_PC(2);
	else
	ADD_PC(1);
}
void dcfsnz(uint8_t *code){
	int result=rawDecOrInc(code,-1);
	if(result!=0)
	ADD_PC(2);
	else
	ADD_PC(1);
}
void incf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int v2=1;
	realresult=rawAdd(v1,v2,0);
	storeFileReg(d,realresult,address);
	ADD_PC(1);
}
void incfsz(uint8_t *code){
	int result=rawDecOrInc(code,1);
	if(result==0)
	ADD_PC(2);
	else
	ADD_PC(1);
}
void infsnz(uint8_t *code){
	int result=rawDecOrInc(code,1);
	if(result!=0)
	ADD_PC(2);
	else
	ADD_PC(1);
}
void movf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int value=GetValue(address);
	SetZnN(value);
	storeFileReg(d,value,address);
	ADD_PC(1);
}
void mulwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int value=GetValue(address);
	value=value*memory[WREG];
	storeFileReg(d,value,address);
	ADD_PC(1);
}
void negf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int v2=v1*2;
	realresult=rawAdd(v1,-v2,0);
	storeFileReg(d,realresult,address);
	ADD_PC(1);
}
void rlcf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	uint8_t Cbit=STATUS->C;
	STATUS->C=(v1>>7)&0x01;
	v1=(v1<<1)|Cbit;
	SetZnN(v1);
	storeFileReg(d,v1,address);
	ADD_PC(1);
}
void rlncf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	uint8_t Cbit=(v1>>7)&0x01;
	v1=(v1<<1)|Cbit;
	SetZnN(v1);
	storeFileReg(d,v1,address);
	ADD_PC(1);
}
void rrcf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	uint8_t Cbit=STATUS->C;
	STATUS->C=(v1)&0x01;
	v1=(v1>>1)|(Cbit<<7);
	SetZnN(v1);
	storeFileReg(d,v1,address);
	ADD_PC(1);
}
void rrncf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	int v1=GetValue(address);
	uint8_t Cbit=(v1)&0x01;
	v1=(v1>>1)|(Cbit<<7);
	SetZnN(v1);
	storeFileReg(d,v1,address);
	ADD_PC(1);
}
void swapf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t value=GetValue(address);
	uint8_t v1=(value&0x0F)<<4;
	uint8_t v2=(value&0xF0)>>4;
	value=v1|v2;
	storeFileReg(d,value,address);
	ADD_PC(1);
}
void tstfsz(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t value=GetValue(address);
	if(value==0)
		ADD_PC(2);
	else
		ADD_PC(1);
}
void xorwf(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t v1=GetValue(address);
	uint8_t v2=GetValue(WREG);
	uint8_t result=v1^v2;
	storeFileReg(d,result,address);
	ADD_PC(1);
}
void addlw(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	uint8_t realresult;
	int v1=*(code+1);
	int v2=GetValue(WREG);
	realresult=rawAdd(v1,v2,0);
	memory[WREG]=realresult;
	ADD_PC(1);
}
void andlw(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	uint8_t realresult;
	int v1=*(code+1);
	int v2=GetValue(WREG);
	realresult=v1&v2;
	memory[WREG]=realresult;
	SetZnN(realresult);
	ADD_PC(1);
}
void mullw(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	uint16_t realresult;
	int v1=*(code+1);
	int v2=GetValue(WREG);
	realresult=v1*v2;
	memory[PRODH]=realresult>>8;
	memory[PRODL]=realresult&0xFF;
	ADD_PC(1);
}
void sublw(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	uint16_t realresult;
	int v1=*(code+1);
	int v2=GetValue(WREG);
	realresult=rawAdd(v1,-v2,0);
	storeFileReg(d,realresult,WREG);
	if(realresult<0x80)
		STATUS->C=1;
	else
		STATUS->C=0;
	ADD_PC(1);
}
void xorlw(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	uint16_t realresult;
	int v1=*(code+1);
	int v2=GetValue(WREG);
	realresult=v1^v2;
	memory[WREG]=realresult;
	ADD_PC(1);
}
void iorlw(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	uint16_t realresult;
	int v1=*(code+1);
	int v2=GetValue(WREG);
	realresult=v1|v2;
	memory[WREG]=realresult;
	ADD_PC(1);
}
void goto1(uint8_t *code){
	uint8_t v70=*(code+1);
	uint8_t v158=*(code+3);
	uint8_t v1916=*(code+2)&0xF;
	PCL=v70;
	PCLATH=v158;
	PCLATU=v1916;
}
void subwfb(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int v1=GetValue(address);
	int C=(~(STATUS->C))&0x01;
	//storeFileReg(d,C,address);
	int v2=(GetValue(WREG))+C;
	realresult=rawAdd(v1,-v2,0);
	storeFileReg(d,realresult,address);

	if(realresult<0x80)
		STATUS->C=1;
	else
		STATUS->C=0;
	ADD_PC(1);
}
void subfwb(uint8_t *code){
	unsigned int a=GetA(code);
	unsigned int d=GetD(code);
	unsigned int address=*(code+1);
	address=GetAbsoluteAddress(a,address);
	uint8_t realresult;
	int C=(~(STATUS->C))&0x01;
	int v1=GetValue(WREG);
	int v2=GetValue(address)+C;
	realresult=rawAdd(v1,-v2,0);
	storeFileReg(d,realresult,address);
	if(realresult<0x80)
		STATUS->C=1;
	else
		STATUS->C=0;
	ADD_PC(1);
}
