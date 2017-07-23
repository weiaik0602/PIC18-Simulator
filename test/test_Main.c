#include "unity.h"
#include "Simulator.h"
#include <stdio.h>
#include <stdint.h>



void setUp(void){}

void tearDown(void){}

void test_GetValue_expect_0x11from0x444(void){
	memory[0x444]=0x11;
	memory[0x44]=0x22;
	*BSR=4;
	int x=GetValue(1,0x44);
	TEST_ASSERT_EQUAL_HEX16(x,0x11);
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

void test_addwf_expect_0xFE_C_1(void){
	uint32_t code[]={0x2212};
	*WREG=0xFF;
	memory[0x12]=0xFF;
	addwf(*code);
	TEST_ASSERT_EQUAL(Status.C,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xFE);
}

void test_subwf_expect(void){
	uint32_t code[]={0x2212};
	*WREG=0x22;
	memory[0x12]=0x11;
	subwf(*code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xEF);
	TEST_ASSERT_EQUAL(Status.N,1);
	
}
/*

void test_bcf_expect_wreg_is_0x88(void)
{
  movlw(0x00FF);
  movwf(0x0E11);   //memory 0x11 with the value 0xFF
  ShowWREG();
  ShowMemory(0x11);
	bcf(0x9C11);      //clear the 6th bit of the memory ox11
	ShowMemory(0x11);   //memory 0x11 now expected 0xBF(1111 1111 -> 1011 1111)
}

void test_bsf_expect_wreg_is_0x88(void)
{
  movlw(0x0000);
  movwf(0x0E11);   //memory 0x11 with the value 0x00
  ShowWREG();
  ShowMemory(0x11);
	bsf(0x8C11);      //set the 6th bit of the memory ox11
	ShowMemory(0x11);   //memory 0x11 now expected 0x40(0000 0000  -> 0100 0000)
}

void test_setf_and_clrf_expect(void){
  movlw(0x0088);
  ShowPC();
  movwf(0x0E14);    //memory 0x14 with the value 0x0088
  ShowPC();
  ShowMemory(0x14);
  setf(0x6814);     //memory 0x14 expected 0xFF
  ShowPC();
  ShowMemory(0x14);
  clrf(0x0014);     //memory 0x14 expected 0x00
  ShowPC();
  ShowMemory(0x14);
}

void test_btfsc_btfss_expect(void){
  movlw(0x0080);
  movwf(0x0E88);   //memory 0x88 with the value 0x80
  btfss(0x0E88);   //test the 7th bit in the memory 0x88,skip if it is 1
  movlw(0x00EE);
  ShowWREG();      //WREG expected 0x80 as we skip the movlw instruction

  movlw(0x00DF);
  movwf(0x0E88);   //memory 0x88 with the value 0xDF(1101 1111)
  btfsc(0x0A88);   //test the 5th bit in the memory 0x88,skip if it is 0
  movlw(0x00EE);
  ShowWREG();      //WREG expected 0x80 as we skip the movlw instruction
  ShowPC();
  nop();
  nop();
  nop();
  nop();
  ShowPC();
}

void test_movff_expect(void){
  movlw(0x0044);
  ShowPC();
  movwf(0x0E55);
  ShowPC();
  movff(0xC055F088);
  ShowPC();
  ShowMemory(0x088);
  ShowMemory(0x055);
	printf("%#04x",sizeof(int));
}
*/
void test_bc_expect(void){
	Status.C=1;
	movlw(0x0055);
	nop();
	nop();
	nop();
	nop();
	nop();
	ShowPC();
	bnc(0x0001);
	ShowPC();
	//system("break");
}/*
void test_bnc_expect(void){
	//Status.C=0;
	ShowWREG();
	//system("clear");
}*/
