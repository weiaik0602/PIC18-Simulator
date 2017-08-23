#include "Simulator.h"
#include "GlobalVariable.h"
#include "Function.h"
#include "Exception.h"
#include "CException.h"
#include <stdio.h>
#include <stdint.h>

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
  [0x1C]={comf},
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
  [0x4B]={infsnz},
  [0x10]={iorwf},
  [0x11]={iorwf},
  [0x12]={iorwf},
  [0x13]={iorwf},
  [0x50]={movf},
  [0x51]={movf},
  [0x52]={movf},
  [0x53]={movf},
  [0x6E]={movwf},
  [0x6F]={movwf},
  [0x02]={mulwf},
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
  [0x43]={rrncf},
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
  [0x5B]={subwfb},*/
  [0x38]={swapf},
  [0x39]={swapf},
  [0x3A]={swapf},
  [0x3B]={swapf},
  [0x67]={tstfsz},
  [0x68]={tstfsz},
  [0x18]={xorwf},
  [0x19]={xorwf},
  [0x1A]={xorwf},
  [0x1B]={xorwf},
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
  [0xAF]={btfss},
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
  [0x7F]={btg},
  [0xE1]={bnz},
  [0xE2]={bc},
  [0xE3]={bnc},
  [0xE4]={bov},
  [0xE5]={bnov},
  [0xE6]={bn},
  [0xE7]={bnn},
  [0x08]={sublw},
  [0x09]={iorlw},
  [0x0A]={xorlw},
  [0x0B]={andlw},
//  [0x0C]={retlw},
  [0x0D]={mullw},
  [0x0F]={addlw},
  [0x01]={movlb},
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
  [0xFF]={nop},
  //[0xEC]={call},
  //[0xED]={call},
  [0xEF]={goto1},/*
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
		case(0x00):nop(code);
								break;
		case(0x07):daw();
							 break;
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
			default:break;
	};
}

void printErrorMessage(uint16_t opcode){
	printf("ERROR !!! 0x%4x this opcode not valid!!! Will not continue execute\n",opcode);
}
void simulateInstruction(int numberOfInstruction){
	int temp=GET_PC();
	int i=0;
	while(i<numberOfInstruction){
		if(OpcodeTable[flash[temp]].execute==0){
			printErrorMessage((flash[temp]<<8)|flash[temp+1]);
			i=2*MB;
		}
		else
			OpcodeTable[flash[temp]].execute(&flash[temp]);
		i++;
		}
}
void simulateAll(){
  int i=0;
  while(i<2*MB){
		if(OpcodeTable[flash[i]].execute==0){
			 printErrorMessage((flash[i]<<8)|flash[i+1]);
			 i=2*MB;
		 }
		else{
     OpcodeTable[flash[i]].execute(&flash[i]);
     i=GET_PC();
	 	}
   }
}
void simulateInstruction1(int numberOfInstruction){
	int temp=GET_PC();
	int i=0;
	while(i<numberOfInstruction){
		if(OpcodeTable[flash[temp]].execute==0){
			throwException(temp,"\nsafag");
			i=2*MB;
		}
		else
			OpcodeTable[flash[temp]].execute(&flash[temp]);
		i++;
		}
}
