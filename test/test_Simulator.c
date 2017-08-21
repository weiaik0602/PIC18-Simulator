#include "unity.h"
#include "Simulator.h"
#include "GlobalVariable.h"
#include "RawFunction.h"
#include "Function.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>


void setUp(void){}

void tearDown(void){}


///////////////////////////////////////////////////////////

void test_Simulate_expect_all_instruction_can_run(void){
	uint8_t code[]={0x0E,0x11,     //movlw 0x11
									0x6E,0x56,   //movwf 0x56
									0xA8,0x56,   //btfss 0x56
									0xC0,0xFF,   //movff 0xFF,0x12;
									0xF0,0x12};
	CLEAR_PC();
	ClrStatus();
	memory[0xFF]=0x14;
	memory[0x12]=0;
	int size=sizeof(code);
	memcpy(flash,code,size);
	Simulate(size);

	//1st instruction line movlw 0x12
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x11);
	//2nd instruction line movwf 0x56
	TEST_ASSERT_EQUAL_HEX16(memory[0x56],0x11);
	//3rd instruction line btfsc 0x56
	//(1000 1000)<-testing if the 4th bit is clear
	//4th intruction line movff 0xFF,0x12(should be skipped)
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x00);
}
