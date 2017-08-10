#include "unity.h"
#include "Simulator.h"
#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>


void setUp(void){}

void tearDown(void){}

void test_GetA_expect_get1(void){
	uint8_t code[]={0x01,0x00};
	int result=GetA(code);
	TEST_ASSERT_EQUAL(result,1);
}
void test_GetD_expect_get1(void){
	uint8_t code[]={0x02,0x00};
	int result=GetD(code);
	TEST_ASSERT_EQUAL(result,1);
}
void test_GetB_expect_get7(void){
	uint8_t code[]={0xFF,0x00};
	int result=GetB(code);
	TEST_ASSERT_EQUAL(result,7);
}
void test_ChangeAddressWithBSR_expect_address_is_0x512(void){
	*BSR=5;
	uint16_t address=0x12;
	address=ChangeAddressWithBSR(0x12);
	TEST_ASSERT_EQUAL_HEX16(address,0x512);
}
void test_SET_PC_expect_PC_0x88(void){
	SET_PC(0x88);
	TEST_ASSERT_EQUAL(GET_PC(),0x88);
}
void test_CLEAR_PC_expect_PC_0(void){
	CLEAR_PC();
	TEST_ASSERT_EQUAL(GET_PC(),0);
}
void test_storeFileReg_d0_a0_88_ff_expect_88inWREG(void){
	storeFileReg(0,0,0x88,0xFF);
	TEST_ASSERT_EQUAL_HEX16(*WREG,0x88);
}
void test_storeFileReg_d0_a1_88_ff_expect_88inWREG(void){
	storeFileReg(0,1,0x88,0xFF);
	TEST_ASSERT_EQUAL_HEX16(*WREG,0x88);
}
void test_storeFileReg_d1_a0_88_ff_expect_88in0xFF(void){
	storeFileReg(1,0,0x88,0xFF);
	TEST_ASSERT_EQUAL_HEX16(memory[0xFF],0x88);
}
void test_storeFileReg_d1_a1_88_ff_expect_88in0x5FF(void){
	*BSR=5;
	storeFileReg(1,1,0x88,0xFF);
	TEST_ASSERT_EQUAL_HEX16(memory[0x5FF],0x88);
}
void test_GetValue_expect_0x11from0x444(void){
	memory[0x444]=0x11;
	*BSR=4;
	int result=GetValue(1,0x44);
	TEST_ASSERT_EQUAL_HEX16(result,0x11);
}
void test_GetValue_expect_0x11from0x55(void){
	memory[0x55]=0x11;
	*BSR=4;
	int result=GetValue(0,0x55);
	TEST_ASSERT_EQUAL_HEX16(result,0x11);
}
void test_rawAdd_0x0F_0x1_expect_DC1_0x10(void){
	int v1=0x0F;
	int v2=0x1;
	ClrStatus();
	unsigned int result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->DC,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x10);
}
void test_rawAdd_0xFF_0x1_expect_DC1_C1_0x1(void){
	int v1=0xFF;
	int v2=0x1;
	ClrStatus();
	char result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->DC,1);
	TEST_ASSERT_EQUAL_HEX16(Status->C,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x0);
}
void test_rawAdd_0x1_minus0x1_expect_DC0_Z1_0x0(void){
	int v1=0x1;
	int v2=0x1;
	ClrStatus();
	char result=rawAdd(v1,-v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->Z,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x0);
}
void test_rawAdd_0x0_minus0x1_expect_N1_0xFF(void){
	int v1=0x0;
	int v2=0x1;
	ClrStatus();
	uint8_t result=rawAdd(v1,-v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->N,1);
	TEST_ASSERT_EQUAL_HEX16(result,0xFF);
}
void test_rawAdd_0x40_0x40_expect_OV1_0x80(void){
	int v1=0x40;     //2 positive num get neg num
	int v2=0x40;
	ClrStatus();
	uint8_t result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->OV,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x80);
}
void test_rawAdd_0x7_0x6_expect_OV1_0x80(void){
	int v1=0x81;     //2 neg number get positive num
	int v2=0x7F;
	ClrStatus();
	uint8_t result=rawAdd(v1,-v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->OV,1);
	TEST_ASSERT_EQUAL_HEX16(result,0x02);
}
void test_rawAdd_neg0x3_0x6_expect_OV0_0x03(void){
	int v1=0x6;     //2 neg number get positive num
	int v2=-(0x3);
	ClrStatus();
	uint8_t result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->OV,0);
	TEST_ASSERT_EQUAL_HEX16(result,0x03);
}
void test_rawAdd_0x3_neg0x6_expect_OV0_neg3(void){
	int v1=-(0x6);     //2 neg number get positive num
	int v2=0x3;
	ClrStatus();
	uint8_t result=rawAdd(v1,v2,0);
	TEST_ASSERT_EQUAL_HEX16(Status->OV,0);
	TEST_ASSERT_EQUAL_HEX16(result,0xFD);
}
void test_ClrStatus_expect_Status_0(void){
	Status->C=1;
	ClrStatus();
	TEST_ASSERT_EQUAL_HEX16(memory[0xFD8],0);
}
void test_SetZnN_expect_Z1_N0(void){
	ClrStatus();
	SetZnN(0x00);
	TEST_ASSERT_EQUAL_HEX16(Status->Z,1);
	TEST_ASSERT_EQUAL_HEX16(Status->N,0);
}
void test_SetZnN_expect_Z0_N1(void){
	ClrStatus();
	SetZnN(0x80);
	TEST_ASSERT_EQUAL_HEX16(Status->Z,0);
	TEST_ASSERT_EQUAL_HEX16(Status->N,1);
}

///////////////////////////////////////////////////////////
void test_movlb_expect_BSR_is_0x05(void){
	uint8_t code[]={0x01,0x05};
	movlb(code);
	TEST_ASSERT_EQUAL(*BSR,0x5);
}
void test_movlw_expect_wreg_is_0x88(void){
	uint8_t code[]={0x0F,0x88};
	movlw(code);
	TEST_ASSERT_EQUAL_HEX16(*WREG,0x88);
}
void test_movwf_expect(void){
	uint8_t code[]={
		0x0F, 0x99,							//movlw 0x99
	  0x6E, 0x9E};           //movwf 0x9E,ACCESS
	//a=0,no BSR
	ClrStatus();
	movlw(code);
	movwf(code+2);
	TEST_ASSERT_EQUAL(*WREG,0x99);    //expect WREG with the value 0x99
	TEST_ASSERT_EQUAL(memory[0x9E],0x99); //expect memory 0x9E with the value 0x99
}
void test_addwf_expect_0x10_C_0_DC_1(void){
	uint8_t code[]={0x22, 0x12};
	*WREG=0x0F;
	memory[0x12]=0x01;
	ClrStatus();
	addwf(code);
	TEST_ASSERT_EQUAL(Status->C,0);
	TEST_ASSERT_EQUAL(Status->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x10);
}
void test_subwf_0x11minus0x22_expect_0xEF_N_1(void){
	uint8_t code[]={0x22,0x12};
	*WREG=0x22;
	memory[0x12]=0x11;
	subwf(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xEF);
	TEST_ASSERT_EQUAL(Status->N,1);
}
void test_bcf_expect_0xBF(void){
	uint8_t code[]={0x9C,0x11};
  memory[0x11]=0xFF;
	bcf(code);      //clear the 6th bit of the memory ox11
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0xBF);   //memory 0x11 now expected 0xBF(1111 1111 -> 1011 1111)
}
void test_bsf_expect_0x40(void){
	uint8_t code[]={0x8C,0x11};
  memory[0x11]=0x00;
	bsf(code);      //set the 6th bit of the memory ox11
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0x40);   //memory 0x11 now expected 0x40(0000 0000  -> 0100 0000)
}
void test_setf_expect_0xFF(void){
	uint8_t code[]={0x68,0x14};
  memory[0x14]=0x89;
  setf(code);     //memory 0x14 expected 0xFF
	TEST_ASSERT_EQUAL_HEX16(memory[0x14],0xFF);
}
void test_clrf_expect_0x00(void){
	uint8_t code[]={0x00,0x14};
  memory[0x14]=0x89;
  clrf(code);     //memory 0x14 expected 0x00
	TEST_ASSERT_EQUAL_HEX16(memory[0x14],0x00);
}
void test_movff_expect_0x44_moved_to_0x88(void){
	uint8_t code[]={0xC0,0x55,
									0xF0,0x88};
	memory[0x55]=0x44;
  movff(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x88],0x44);
}
void test_btfss_expect_skip(void){
	uint8_t code[]={0x0E,0x88,
									0x00,0xEE};
  memory[0x88]=0x80;
	CLEAR_PC();
	*WREG=0x80;
  btfss(code);   //test the 7th bit in the memory 0x88,skip if it is 1
  movlw(code+1);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x6) ;     //WREG expected 0x80 as we skip the movlw instruction

}
void test_btfsc_expect_skip(void){
	uint8_t code[]={0x0A,0x88,
									0x00,0xEE};
  memory[0x88]=0xDF;    //memory 0x88 with the value 0xDF(1101 1111)
	*WREG=0x80;
	CLEAR_PC();
  btfsc(code);   //test the 5th bit in the memory 0x88,skip if it is 0
	movlw(code+2);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x6) ;//WREG expected 0x80 as we skip the movlw instruction
}
void test_bc_expect_PC_0x08(void){
	uint8_t code[]={0x00,0x55,
									0x00,0x00,
									0x00,0x01};
	CLEAR_PC();
	Status->C=1;
	movlw(code);
	nop(code+2);
	bc(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnc_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,
									0x00,0xFE};
	CLEAR_PC();
	Status->C=0;
	movlw(code);
	bnc(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bz_expect_PC_0x08(void){
	uint8_t code[]={0x00,0x55,
									0x00,0x00,
									0x00,0x01};
	CLEAR_PC();
	Status->Z=1;
	movlw(code);
	nop(code+2);
	bz(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnz_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,
									0x00,0xFE};
	CLEAR_PC();
	Status->Z=0;
	movlw(code);
	bnz(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bov_expect_PC_0x08(void){
	uint8_t code[]={0x00,0x55,
									0x00,0x00,
									0x00,0x01};
	CLEAR_PC();
	Status->OV=1;
	movlw(code);
	nop(code+2);
	bov(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnov_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,
									0x00,0xFE};
	CLEAR_PC();
	Status->OV=0;
	movlw(code);
	bnov(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_addwfc_expect_0x11_C_0_DC_1(void){
	uint8_t code[]={0x22,0x12};
	ClrStatus();
	*WREG=0x0F;
	Status->C=1;
	memory[0x12]=0x01;
	addwfc(code);
	TEST_ASSERT_EQUAL(Status->C,0);
	TEST_ASSERT_EQUAL(Status->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x11);
}
void test_andwf_0xFF_and_0xFF_expect_0xFF_Z0_N1(void){
	ClrStatus();
	uint8_t code[]={0x02,0x12};
	*WREG=0xFF;
	memory[0x12]=0xFF;
	andwf(code);
	TEST_ASSERT_EQUAL(Status->Z,0);
	TEST_ASSERT_EQUAL(Status->N,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xFF);
}
void test_andwf_0xFF_and_0x00_expect_0x00_Z1_N0(void){
	ClrStatus();
	uint8_t code[]={0x02,0x12};
	*WREG=0x00;
	memory[0x12]=0xFF;
	andwf(code);
	TEST_ASSERT_EQUAL(Status->Z,1);
	TEST_ASSERT_EQUAL(Status->N,0);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x00);
}
void test_comf_0x80_expect_0x7F(void){
	uint8_t code[]={0x12,0x12};
	memory[0x12]=0x80;
	comf(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x7F);
}
void test_iorwf_0x13_0x91_expect_0x93(void){
		uint8_t code[]={0x12,0x88};
		memory[0x88]=0x13;
		*WREG=0x91;
		iorwf(code);
		TEST_ASSERT_EQUAL_HEX16(memory[0x88],0x93);
}
void test_Simulate(void){
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
	memcpy(RAM,code,sizeof(code));
	Simulate(size);

	//1st instruction line movlw 0x12
	TEST_ASSERT_EQUAL_HEX16(*WREG,0x11);
	//2nd instruction line movwf 0x56
	TEST_ASSERT_EQUAL_HEX16(memory[0x56],0x11);
	//3rd instruction line btfsc 0x56
	//4th intruction line movff 0xFF,0x12(should be skipped)
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x00);

}
