#include "unity.h"
#include "Main.h"
#include <stdio.h>
#include <stdint.h>
//#include "Functions.h"


void setUp(void){

}

void tearDown(void){}

/*
void test_movlb_expect_BSR_is_0x05(void)
{
	movlb(0x0105);
	ShowBSR();
}
void test_movlw_expect_wreg_is_0x88(void)
{
	movlw(0x0F88);
	ShowWREG();
}

void test_movwf_expect(void){
	//a=1 BSR=5
	movlb(0x0105);
	movlw(0x0F99);
	movwf(0x6F9E);
	ShowWREG();
	ShowMemory(0x59E);
//a=0,no BSR
	movlw(0x0F99);
	movwf(0x6E9E);
	ShowWREG();
	ShowMemory(0x9E);
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
	subwf(0x5C9E);   //d and a is set to 0
	ShowWREG();        //WREG expected 0x00
	ShowMemory(0x9E);   //0x9E expected 0x11
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
  movwf(0x0E14);    //memory 0x14 with the value 0x0088
  ShowMemory(0x14);
  setf(0x6814);     //memory 0x14 expected 0xFF
  ShowMemory(0x14);
  clrf(0x0014);     //memory 0x14 expected 0x00
  ShowMemory(0x14);
}*/
