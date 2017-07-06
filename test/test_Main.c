#include "unity.h"
#include "Main.h"
#include <stdio.h>
#include <stdint.h>
//#include "Functions.h"


void setUp(void){
	
}

void tearDown(void){}

void test_Main_expect_k_is_0xff(void)
{
	int x=movlw(0x0EFF);
	printf("the address of WREG now is %#06x\n", WREG);
	printf("the value of WREG now is %#06x\n",*WREG);
	TEST_ASSERT_EQUAL_HEX16(0,0xff);
}
