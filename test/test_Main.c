#include "unity.h"
#include "Main.h"
#include <stdio.h>
#include "Functions.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_Main_expect_k_is_0xff(void)
{
  unsigned short WREG;
  printf("the address of working register now is %#06x\n", &WREG); 
  WREG=Opcode(0x0E22);
  printf("the working register now is %#06x\n",WREG);
  TEST_ASSERT_EQUAL_HEX16(WREG,0xff);
}
