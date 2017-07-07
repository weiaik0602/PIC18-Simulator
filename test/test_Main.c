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
	int x=movlw(0x0F88);
	printf("the address of WREG now is %#06x\n", &WREG);
	printf("the address of WREG now is %#06x\n", WREG);
	printf("the value of WREG now is %#06x\n",*WREG);
	printf("the value of 0xFE8 now is %#06x\n",memory[0xFE8]);
	TEST_ASSERT_EQUAL_HEX16(x,0x00);
}

void test_movwf_expect(void){
	int a;
	int x=movlw(0x0F99);
	a=movwf(0x6F9E);

	TEST_ASSERT_EQUAL_HEX16(a,0x0);
	printf("the address of WREG now is %#06x\n", WREG);
	printf("the value of WREG now is %#06x\n",*WREG);
	printf("the value of 0xFE8 now is %#06x\n",memory[0xFE8]);
	printf("the address of BSR now is %#06x\n", BSR);
	printf("the value of BSR now is %#06x\n",*BSR);
	printf("the memory of 0x59E now is %#06x\n",memory[0x59E]);
	printf("the memory of 0x59E now is %#06x\n",memory[0xFE8]);
}
