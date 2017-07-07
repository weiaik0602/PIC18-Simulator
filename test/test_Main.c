#include "unity.h"
#include "Main.h"
#include <stdio.h>
#include <stdint.h>
//#include "Functions.h"


void setUp(void){

}

void tearDown(void){}

void test_movlw_expect_wreg_is_0x88(void)
{
	int x=movlw(0x0E88);
	printf("the address of WREG now is %#06x\n", WREG);
	printf("the value of WREG now is %#06x\n",*WREG);
	TEST_ASSERT_EQUAL_HEX16(x,0x00);
}

void test_movwf_expect(void){
	int a;
	a=movwf(0x6E9E);
	TEST_ASSERT_EQUAL_HEX16(a,0x01);
}
