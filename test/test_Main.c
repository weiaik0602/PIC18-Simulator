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
  
  WREG=Opcode(0x0E22);
  printf("%#010x\n", WREG); 
  TEST_ASSERT_EQUAL_HEX(WREG,0xff);
}
