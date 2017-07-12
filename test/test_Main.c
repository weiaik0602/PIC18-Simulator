#include "unity.h"
#include "Simulator.h"
#include <stdio.h>
#include <stdint.h>



void setUp(void){}

void tearDown(void){}

/*
void test_movlb_expect_BSR_is_0x05(void)
{
	movlb(0x0105);
	TEST_ASSERT_EQUAL(*BSR,0x5);
}

void test_movlw_expect_wreg_is_0x88(void)
{
	movlw(0x0F88);
	TEST_ASSERT_EQUAL(*WREG,0x88);
}

void test_movwf_expect(void){
	//a=1 BSR=5
	movlb(0x0105);
	movlw(0x0F99);
	movwf(0x6F9E);
	TEST_ASSERT_EQUAL(*WREG,0x99);    //expect WREG with the value 0x99
	TEST_ASSERT_EQUAL(memory[0x59E],0x99); //expect memory 0x59E with the value 0x99
//a=0,no BSR
	movlw(0x0F99);
	movwf(0x6E9E);
	TEST_ASSERT_EQUAL(*WREG,0x99);    //expect WREG with the value 0x99
	TEST_ASSERT_EQUAL(memory[0x9E],0x99); //expect memory 0x9E with the value 0x99
}


void test_addwf_expect(void){
	movlb(0x0105);  //BSR=5

	//if a=0 BSR=0
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	addwf(0x249E);   //d and a is set to 0
	ShowWREG();        //WREG expected 0x22
	ShowMemory(0x9E);   //0x9E expected 0x11
	//if a=0 BSR=1
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	addwf(0x269E);   //d=1 and a=0
	ShowWREG();        //WREG expected 0x11
	ShowMemory(0x9E);   //0x9E expected 0x22
	//if a=1 BSR=0
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	addwf(0x259E);   //d=0 and a=1
	ShowWREG();        //WREG expected 0x22
	ShowMemory(0x59E);   //0x59E expected 0x11
	//if a=1 BSR=1
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	addwf(0x279E);   //d=1 and a=1
	ShowWREG();        //WREG expected 0x11
	ShowMemory(0x59E);   //0x59E expected 0x22
}

void test_subwf_expect(void){
	movlb(0x0105);  //BSR=5

	//if a=0 BSR=0
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
  movlw(0x0E12);
	subwf(0x5C9E);   //d and a is set to 0
	ShowWREG();        //WREG expected 0x00
	ShowMemory(0x9E);   //0x9E expected 0x11
  ShowC();
  ShowN();
	//if a=0 BSR=1
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	subwf(0x5E9E);   //d=1 and a=0
	ShowWREG();        //WREG expected 0x11
	ShowMemory(0x9E);   //0x9E expected 0x00
	//if a=1 BSR=0
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	subwf(0x5D9E);   //d=0 and a=1
	ShowWREG();        //WREG expected 0x00
	ShowMemory(0x59E);   //0x59E expected 0x11
	//if a=1 BSR=1
	movlw(0x0E11);  //WREG=0x11
	movwf(0x6F9E);  //memory 0x59E=0x11
	movwf(0x6E9E);  //memory 0x9E =0x11
	subwf(0x5F9E);   //d=1 and a=1
	ShowWREG();        //WREG expected 0x11
	ShowMemory(0x59E);   //0x59E expected 0x00

}

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
}*/
void test_bc_expect(void){
	C=0;
	nop();
	nop();
	nop();
	nop();
	ShowPC();
	bc(0x00FD);
	ShowPC();
}
