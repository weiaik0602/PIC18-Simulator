#include "unity.h"
#include "RawFunction.h"
#include "GlobalVariable.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_GetA_expect_get1(void){
	uint8_t code[]={0x01,0x00};
	int result=GetA(code);
	TEST_ASSERT_EQUAL(result,1);
}
void test_GetA_expect_get0(void){
	uint8_t code[]={0x02,0x00};
	int result=GetA(code);
	TEST_ASSERT_EQUAL(result,0);
}
void test_GetD_expect_get1(void){
	uint8_t code[]={0x02,0x00};
	int result=GetD(code);
	TEST_ASSERT_EQUAL(result,1);
}
void test_GetD_expect_get0(void){
	uint8_t code[]={0x01,0x00};
	int result=GetD(code);
	TEST_ASSERT_EQUAL(result,0);
}
void test_GetB_expect_get7(void){
	uint8_t code[]={0xFF,0x00};
	int result=GetB(code);
	TEST_ASSERT_EQUAL(result,7);
}
void test_GetB_expect_get2(void){
	uint8_t code[]={0xF4,0x00};
	int result=GetB(code);
	TEST_ASSERT_EQUAL(result,2);
}
void test_GetAbsoluteAddress_expect_address_0x512(void){
	memory[BSR]=0x5;
	unsigned int address;
	address=GetAbsoluteAddress(1,0x12);
	TEST_ASSERT_EQUAL_HEX16(address,0x512);
}
void test_GetAbsoluteAddress_expect_address_0x5FF(void){
	memory[BSR]=0x5;
	unsigned int address;
	address=GetAbsoluteAddress(1,0xFF);
	TEST_ASSERT_EQUAL_HEX16(address,0x5FF);
}
void test_GetAbsoluteAddress_expect_address_0x12(void){
	memory[BSR]=0x5;
	unsigned int address;
	address=GetAbsoluteAddress(0,0x12);
	TEST_ASSERT_EQUAL_HEX16(address,0x12);
}
void test_GetAbsoluteAddress_expect_address_0xFAE(void){
	memory[BSR]=0x5;
	unsigned int address;
	address=GetAbsoluteAddress(0,0x80);
	TEST_ASSERT_EQUAL_HEX16(address,0xF80);
}
void test_SET_PC_expect_PC_0x88(void){
	SET_PC(0x88);
	TEST_ASSERT_EQUAL(GET_PC(),0x88);
}
void test_SET_PC_expect_PC_0x22(void){
	SET_PC(0x22);
	TEST_ASSERT_EQUAL(GET_PC(),0x22);
}
void test_CLEAR_PC_expect_PC_0(void){
	CLEAR_PC();
	TEST_ASSERT_EQUAL(GET_PC(),0);
}
void test_storeFileReg_d0_expect_88inWREG(void){
	storeFileReg(0,0x88,0xFF);
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x88);
}
void test_storeFileReg_d1_expect_88in0x5FF(void){
	storeFileReg(1,0x88,0x5FF);
	TEST_ASSERT_EQUAL_HEX16(memory[0x5FF],0x88);
}
void test_storeFileReg_d1_expect_88in0x11(void){
	storeFileReg(1,0x88,0x11);
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0x88);
}
void test_GetValue_expect_0x11from0x444(void){
	memory[0x444]=0x11;
	int result=GetValue(0x444);
	TEST_ASSERT_EQUAL_HEX16(result,0x11);
}
void test_GetValue_expect_0x11from0x55(void){
	memory[0x55]=0x11;
	int result=GetValue(0x55);
	TEST_ASSERT_EQUAL_HEX16(result,0x11);
}
void test_rawAdd_0x0F_0x1_expect_DC1_0x10(void){
	int v1=0x0F;
	int v2=0x1;
	ClrStatus();
	unsigned int result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->DC,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x10);
}
void test_rawAdd_0xFF_0x1_expect_DC1_C1_0x1(void){
	int v1=0xFF;
	int v2=0x1;
	ClrStatus();
	char result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->DC,1);
	TEST_ASSERT_EQUAL_HEX16(STATUS->C,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x0);
}
void test_rawAdd_0x1_minus0x1_expect_DC0_Z1_0x0(void){
	int v1=0x1;
	int v2=0x1;
	ClrStatus();
	char result=rawAdd(v1,-v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->Z,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x0);
}
void test_rawAdd_0x0_minus0x1_expect_N1_0xFF(void){
	int v1=0x0;
	int v2=0x1;
	ClrStatus();
	uint8_t result=rawAdd(v1,-v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->N,1);
	TEST_ASSERT_EQUAL_HEX16(result,0xFF);
}
void test_rawAdd_0x40_0x40_expect_OV1_0x80(void){
	int v1=0x40;     //2 positive num get neg num
	int v2=0x40;
	ClrStatus();
	uint8_t result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->OV,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x80);
}
void test_rawAdd_0x7_0x6_expect_OV1_0x80(void){
	int v1=0x81;     //2 neg number get positive num
	int v2=0x7F;
	ClrStatus();
	uint8_t result=rawAdd(v1,-v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->OV,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x02);
}
void test_rawAdd_neg0x3_0x6_expect_OV0_0x03(void){
	int v1=0x6;     //2 neg number get positive num
	int v2=-(0x3);
	ClrStatus();
	uint8_t result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->OV,0);
	TEST_ASSERT_EQUAL_HEX16(result,0x03);
}
void test_rawAdd_0x3_neg0x6_expect_OV0_neg3(void){
	int v1=-(0x6);     //2 neg number get positive num
	int v2=0x3;
	ClrStatus();
	uint8_t result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->OV,0);
	TEST_ASSERT_EQUAL_HEX16(result,0xFD);
}
void test_ClrStatus_expect_Status_0(void){
	STATUS->C=1;
	ClrStatus();
	TEST_ASSERT_EQUAL_HEX16(memory[0xFD8],0);
}
void test_SetZnN_expect_Z1_N0(void){
	ClrStatus();
	SetZnN(0x00);
	TEST_ASSERT_EQUAL_HEX16(STATUS->Z,1);
	TEST_ASSERT_EQUAL_HEX16(STATUS->N,0);
}
void test_SetZnN_expect_Z0_N1(void){
	ClrStatus();
	SetZnN(0x80);
	TEST_ASSERT_EQUAL_HEX16(STATUS->Z,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->N,1);
}
void test_ClrTBLPTR_expect_TBLPTR_0(void){
	TBLPTRL=0x56;
	ClrTBLPTR();
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0);
}
