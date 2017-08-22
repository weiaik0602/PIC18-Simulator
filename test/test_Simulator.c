#include "unity.h"
#include "Simulator.h"
#include "GlobalVariable.h"
#include "RawFunction.h"
#include "Function.h"
//#include "Exception.h"
//#include "CExceptionConfig.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>


void setUp(void){}

void tearDown(void){}


///////////////////////////////////////////////////////////
/*
void test_Simulate_expect_all_instruction_can_run(void){
	uint8_t code[]={0x0E,0x11,     //movlw 0x11
									0x6E,0x56,   //movwf 0x56
									0xA8,0x56,   //btfss 0x56
									0xC0,0xFF,   //movff 0xFF,0x12;
									0xF0,0x12,
									0xDE,0x11,};
									//0x0E,0xFF};
	//CEXCEPTION_T ex;
	CLEAR_PC();
	ClrStatus();
	memory[0xFF]=0x14;
	memory[0x12]=0x15;
	int size=sizeof(code);
	memcpy(flash,code,size);
	//Try{
	simulateAll();
	//}
	//Catch(ex);
	//1st instruction line movlw 0x12
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x11);
	//2nd instruction line movwf 0x56
	TEST_ASSERT_EQUAL_HEX16(memory[0x56],0x11);
	//3rd instruction line btfsc 0x56
	//(1000 1000)<-testing if the 4th bit is clear
	//4th intruction line movff 0xFF,0x12(should be skipped)
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x15);
}*/
void test_simulate(void){
	uint8_t code[]={0xDE,0x11,
									0xD9,0x44,};
	CLEAR_PC();
	ClrStatus();
	int size=sizeof(code);
	memcpy(flash,code,size);
	simulateInstruction(1);
	simulateInstruction(2);
}
