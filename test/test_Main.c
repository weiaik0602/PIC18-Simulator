#include "unity.h"
#include "Simulator.h"
#include <stdio.h>
#include <stdint.h>



void setUp(void){}

void tearDown(void){}

void test_GetA_expect_get1(void){
	int result=GetA(0x100);
	TEST_ASSERT_EQUAL(result,1);
}
void test_GetD_expect_get1(void){
	int result=GetD(0x200);
	TEST_ASSERT_EQUAL(result,1);
}
void test_GetB_expect_get7(void){
	int result=GetB(0xFF00);
	TEST_ASSERT_EQUAL(result,7);
}
void test_ChangeAddressWithBSR_expect_address_is_with_BSR(void){
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
	memory[0x44]=0x22;
	*BSR=4;
	int x=GetValue(1,0x44);
	TEST_ASSERT_EQUAL_HEX16(x,0x11);
}
void test_rawAdd_0x11_0x11_expect_0x22(void){
	int v1=0x11;
	int v2=0x11;
	unsigned int result=rawAdd(v1,v2);
	TEST_ASSERT_EQUAL_HEX16(result,0x22);
}



///////////////////////////////////////////////////////////
void test_movlb_expect_BSR_is_0x05(void){
	uint32_t code[]={0x0105};
	movlb(*code);
	TEST_ASSERT_EQUAL(*BSR,0x5);
}
void test_movlw_expect_wreg_is_0x88(void){
	uint32_t code[]={0x0F88};
	movlw(*code);
	TEST_ASSERT_EQUAL(*WREG,0x88);
}
void test_movwf_expect(void){
	uint32_t code[]={
		0x0F99, 0x6E9E};        //movlw 0x99, movwf 0x9E,ACCESS
	uint32_t *ptr=code;
	//a=0,no BSR
	movlw(*(ptr));
	movwf(*(ptr+1));
	TEST_ASSERT_EQUAL(*WREG,0x99);    //expect WREG with the value 0x99
	TEST_ASSERT_EQUAL(memory[0x9E],0x99); //expect memory 0x9E with the value 0x99
}
void test_addwf_expect_0x10_C_0_DC_1(void){
	uint32_t code[]={0x2212};
	*WREG=0x0F;
	memory[0x12]=0x01;
	addwf(*code);
	TEST_ASSERT_EQUAL(Status->C,0);
	TEST_ASSERT_EQUAL(Status->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x10);
}
void test_subwf_0x11minus0x22_expect_0xEF_N_1(void){
	uint32_t code[]={0x2212};
	*WREG=0x22;
	memory[0x12]=0x11;
	subwf(*code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xEF);
	TEST_ASSERT_EQUAL(Status->N,1);
}
void test_bcf_expect_0xBF(void){
	uint32_t code[]={0x9C11};
  memory[0x11]=0xFF;
	bcf(*code);      //clear the 6th bit of the memory ox11
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0xBF);   //memory 0x11 now expected 0xBF(1111 1111 -> 1011 1111)
}
void test_bsf_expect_0x40(void){
	uint32_t code[]={0x8C11};
  memory[0x11]=0x00;
	bsf(*code);      //set the 6th bit of the memory ox11
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0x40);   //memory 0x11 now expected 0x40(0000 0000  -> 0100 0000)
}
void test_setf_expect_0xFF(void){
	uint32_t code[]={0x6814};
  memory[0x14]=0x89;
  setf(*code);     //memory 0x14 expected 0xFF
	TEST_ASSERT_EQUAL_HEX16(memory[0x14],0xFF);
}
void test_clrf_expect_0x00(void){
	uint32_t code[]={0x0014};
  memory[0x14]=0x89;
  clrf(*code);     //memory 0x14 expected 0x00
	TEST_ASSERT_EQUAL_HEX16(memory[0x14],0x00);
}
void test_movff_expect_0x44_moved_to_0x88(void){
	uint32_t code[]={0xC055F088};
	memory[0x55]=0x44;
  movff(*code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x88],0x44);
}

void test_btfss_expect_skip(void){
	uint32_t code[]={0x0E88,0x00EE};
  memory[0x88]=0x80;
	CLEAR_PC();
	*WREG=0x80;
  btfss(*code);   //test the 7th bit in the memory 0x88,skip if it is 1
  movlw(*(code+1));
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x6) ;     //WREG expected 0x80 as we skip the movlw instruction

}
void test_btfsc_expect_skip(void){
	uint32_t code[]={0x0A88,0x00EE};
  memory[0x88]=0xDF;    //memory 0x88 with the value 0xDF(1101 1111)
	*WREG=0x80;
	CLEAR_PC();
  btfsc(*code);   //test the 5th bit in the memory 0x88,skip if it is 0
	movlw(*(code+1));
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x6) ;//WREG expected 0x80 as we skip the movlw instruction
}

void test_bc_expect_PC_0x08(void){
	uint32_t code[]={0x0055,0x0000,0x0001};
	CLEAR_PC();
	Status->C=1;
	movlw(*code);
	nop(*(code+1));
	bc(*(code+2));
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnc_expect_PC_0x00(void){
	uint32_t code[]={0x0055,0x0000,0x00FE};
	CLEAR_PC();
	Status->C=0;
	movlw(*code);
	bnc(*(code+2));
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bz_expect_PC_0x08(void){
	uint32_t code[]={0x0055,0x0000,0x0001};
	CLEAR_PC();
	Status->Z=1;
	movlw(*code);
	nop(*(code+1));
	bz(*(code+2));
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnz_expect_PC_0x00(void){
	uint32_t code[]={0x0055,0x0000,0x00FE};
	CLEAR_PC();
	Status->Z=0;
	movlw(*code);
	bnz(*(code+2));
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bov_expect_PC_0x08(void){
	uint32_t code[]={0x0055,0x0000,0x0001};
	CLEAR_PC();
	Status->OV=1;
	movlw(*code);
	nop(*(code+1));
	bov(*(code+2));
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnov_expect_PC_0x00(void){
	uint32_t code[]={0x0055,0x0000,0x00FE};
	CLEAR_PC();
	Status->OV=0;
	movlw(*code);
	bnov(*(code+2));
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_addwfc_expect_0x11_C_0_DC_1(void){
	uint32_t code[]={0x2212};
	*WREG=0x0F;
	Status->C=1;
	memory[0x12]=0x01;
	addwfc(*code);
	TEST_ASSERT_EQUAL(Status->C,0);
	TEST_ASSERT_EQUAL(Status->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x11);
}
void test_andwf_expect(void){
	ClrStatus();
	uint32_t code[]={0x0212};
	*WREG=0xFF;
	memory[0x12]=0xFF;
	andwf(*code);
	TEST_ASSERT_EQUAL(Status->Z,0);
	TEST_ASSERT_EQUAL(Status->N,1);
}
