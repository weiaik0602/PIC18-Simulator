#include "unity.h"
#include "Function.h"
#include "RawFunction.h"
#include "GlobalVariable.h"
#include <string.h>
void setUp(void)
{
}

void tearDown(void)
{
}
void test_tblrd_expect_TABLAT_0x55_TBLPTR_0x00(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x08};    //tblrd*
	memcpy(flash,code,sizeof(code));
	ClrTBLPTR();
	tblrd();
  TEST_ASSERT_EQUAL_HEX16(memory[TABLAT],0x55);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0x00);
}
void test_tblrdposi_expect_TABLAT_0x55_TBLPTR_0x01(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x08};    //tblrd*+
	memcpy(flash,code,sizeof(code));
	ClrTBLPTR();
	tblrdposi();
  TEST_ASSERT_EQUAL_HEX16(memory[TABLAT],0x55);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0x01);
}
void test_tblrdposd_expect_TABLAT_0x0E_TBLPTR_0x01(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x08};    //tblrd*-
	memcpy(flash,code,sizeof(code));
	TBLPTRL=0x01;
	tblrdposd();
  TEST_ASSERT_EQUAL_HEX16(memory[TABLAT],0x0E);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0x00);
}
void test_tblrdprei_expect_TABLAT_0x0E_TBLPTR_0x01(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x08};    //tblrd+*
	memcpy(flash,code,sizeof(code));
	ClrTBLPTR();
	tblrdprei();
  TEST_ASSERT_EQUAL_HEX16(memory[TABLAT],0x0E);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0x01);
}
void test_tblwt_expect_TBLPTR_0(void){
	ClrTBLPTR();
	memory[TABLAT]=0x25;
	storeFileReg(1,0x55,EECON2);
	storeFileReg(1,0xAA,EECON2);
	tblwt();
	TEST_ASSERT_EQUAL_HEX16(tableBuffer[0],0x25);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0);
}
void test_tblwtposi_expect_TBLPTR_0x1(void){
	ClrTBLPTR();
	memory[TABLAT]=0x50;
	storeFileReg(1,0x55,EECON2);
	storeFileReg(1,0xAA,EECON2);
	tblwtposi();
	TEST_ASSERT_EQUAL_HEX16(tableBuffer[0],0x50);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),0x1);
}
void test_tblwtposd_expect_TBLPTR_2(void){
	TBLPTRL=0x03;
	memory[TABLAT]=0x75;
	storeFileReg(1,0x55,EECON2);
	storeFileReg(1,0xAA,EECON2);
	tblwtposd();
	TEST_ASSERT_EQUAL_HEX16(tableBuffer[3],0x75);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),2);
}
void test_tblwtprei_expect_TBLPTR_1(void){
	ClrTBLPTR();
	memory[TABLAT]=0x97;
	storeFileReg(1,0x55,EECON2);
	storeFileReg(1,0xAA,EECON2);
	tblwtprei();
	TEST_ASSERT_EQUAL_HEX16(tableBuffer[1],0x97);
	TEST_ASSERT_EQUAL_HEX16(GET_TBLPTR(),1);
}
void test_daw_expect_WREG_0x05(void){
	uint8_t code[]={0x00,0x07};
	memory[WREG]=0xA5;
	daw();
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x05);
}
void test_daw_expect_WREG_0x34(void){
	uint8_t code[]={0x00,0x07};
	memory[WREG]=0xCE;
	daw();
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x34);
}
void test_movlb_expect_BSR_is_0x05(void){
	uint8_t code[]={0x01,0x05};     //movlb 0x05
	movlb(code);
	TEST_ASSERT_EQUAL(memory[BSR],0x5);
}
void test_movlw_expect_wreg_is_0x88(void){
	uint8_t code[]={0x0E,0x88};    //movlw 0x88
	movlw(code);
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x88);
}
void test_movwf_expect(void){
	uint8_t code[]={
		0x0E, 0x99,							//movlw 0x99
	  0x6E, 0x77};           //movwf 0x77,ACCESS
	//a=0,no BSR
	ClrStatus();
	movlw(code);
	movwf(code+2);
	TEST_ASSERT_EQUAL(memory[WREG],0x99);    //expect WREG with the value 0x99
	TEST_ASSERT_EQUAL(memory[0x77],0x99); //expect memory 0x9E with the value 0x99
}
void test_addwf_expect_0x10_C_0_DC_1(void){
	uint8_t code[]={0x26, 0x12};   //addwf 0x12,f
	storeFileReg(1,0x0F,WREG);
	//*WREG=0x0F;
	memory[0x12]=0x01;
	ClrStatus();
	addwf(code);
	TEST_ASSERT_EQUAL(STATUS->C,0);
	TEST_ASSERT_EQUAL(STATUS->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x10);
}
void test_subwf_0x11minus0x22_expect_0xEF_N_1(void){
	uint8_t code[]={0x5E,0x12};    //subwf 0x12,f
	storeFileReg(1,0x22,WREG);
	//*WREG=0x22;
	memory[0x12]=0x11;
	subwf(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xEF);
	TEST_ASSERT_EQUAL(STATUS->N,1);
}
void test_bcf_expect_0xBF(void){
	uint8_t code[]={0x9C,0x11};   //bcf 0x11
  memory[0x11]=0xFF;
	bcf(code);      //clear the 6th bit of the memory ox11
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0xBF);   //1111 1111 -> 1011 1111
}
void test_bsf_expect_0x40(void){
	uint8_t code[]={0x8C,0x11};  //bsf 0x11
  memory[0x11]=0x00;
	bsf(code);      //set the 6th bit of the memory ox11
	TEST_ASSERT_EQUAL_HEX16(memory[0x11],0x40);   //0000 0000  -> 0100 0000
}
void test_setf_expect_0xFF(void){
	uint8_t code[]={0x68,0x14};   //setf 0x14
  memory[0x14]=0x89;
  setf(code);     //memory 0x14 expected 0xFF
	TEST_ASSERT_EQUAL_HEX16(memory[0x14],0xFF);
}
void test_clrf_expect_0x00(void){
	uint8_t code[]={0x6A,0x14};   //clrf 0x14
  memory[0x14]=0x89;
  clrf(code);     //memory 0x14 expected 0x00
	TEST_ASSERT_EQUAL_HEX16(memory[0x14],0x00);
}
void test_btfss_expect_PC_0x4(void){
	uint8_t code[]={0xAE,0x70,     //btfss 0x70
									0x0E,0xEE};		//movlw 0xEE
  memory[0x70]=0x80;
	CLEAR_PC();
  btfss(code);   //test the 7th bit in the memory 0x88,skip if it is SET
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x4) ;
}
void test_btfsc_expect_PC_0x4(void){
	uint8_t code[]={0xBA,0x70,     //btfsc 0x70
									0x0E,0xEE};    //movlw 0xEE
  memory[0x70]=0xDF;
	CLEAR_PC();
  btfsc(code);   //test the 5th bit in the memory 0x88,skip if it is CLEAR
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x4);
}
void test_nop_expect_PC_0x2(void){
	uint8_t code[]={0x00,0x00};   //nop
	CLEAR_PC();
	nop(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x2);

}
void test_movff_expect_0x44_moved_to_0x88(void){
	uint8_t code[]={0xC0,0x55,    //movff 055,088
									0xF0,0x88};
	memory[0x55]=0x44;
  movff(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x88],0x44);
}
void test_bc_expect_PC_0x08(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x00,    //nop
									0xE2,0x01};   //bc 0x01
	CLEAR_PC();
	STATUS->C=1;
	movlw(code);
	nop(code+2);
	bc(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnc_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,      //movlw 0x55
									0xE3,0xFE};     //bnc 0xFE
	CLEAR_PC();
	STATUS->C=0;
	movlw(code);
	bnc(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bn_expect_PC_0x08(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x00,    //nop
									0xE2,0x01};   //bn 0x01
	CLEAR_PC();
	STATUS->N=1;
	movlw(code);
	nop(code+2);
	bn(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnn_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,      //movlw 0x55
									0xE3,0xFE};     //bnn 0xFE
	CLEAR_PC();
	STATUS->N=0;
	movlw(code);
	bnn(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bz_expect_PC_0x08(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x00,    //nop
									0xE0,0x01};   //bz 0x01
	CLEAR_PC();
	STATUS->Z=1;
	movlw(code);
	nop(code+2);
	bz(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnz_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,      //movlw 0x55
									0xE1,0xFE};     //bnz 0xFE
	CLEAR_PC();
	STATUS->Z=0;
	movlw(code);
	bnz(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_bov_expect_PC_0x08(void){
	uint8_t code[]={0x0E,0x55,    //movlw 0x55
									0x00,0x00,    //nop
									0xE4,0x01};   //bov 0x01
	CLEAR_PC();
	STATUS->OV=1;
	movlw(code);
	nop(code+2);
	bov(code+4);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x08);
}
void test_bnov_expect_PC_0x00(void){
	uint8_t code[]={0x00,0x55,      //movlw 0x55
									0xE5,0xFE};     //bnc 0xFE
	CLEAR_PC();
	STATUS->OV=0;
	movlw(code);
	bnov(code+2);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x00);
}
void test_addwfc_C1expect_0x11_C_0_DC_1(void){
	uint8_t code[]={0x22,0x12};   //addwfc 0x12,f
	ClrStatus();
	memory[WREG]=0x0F;
	STATUS->C=1;
	memory[0x12]=0x01;
	addwfc(code);
	TEST_ASSERT_EQUAL(STATUS->C,0);
	TEST_ASSERT_EQUAL(STATUS->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x11);
}
void test_addwfc_C0expect_0x11_C_0_DC_1(void){
	uint8_t code[]={0x22,0x12};     //addwfc 0x12
	ClrStatus();
	memory[WREG]=0x0F;	//*WREG=0x0F;
	STATUS->C=0;
	memory[0x12]=0x01;
	addwfc(code);
	TEST_ASSERT_EQUAL(STATUS->C,0);
	TEST_ASSERT_EQUAL(STATUS->DC,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x10);
}
void test_andwf_0xFF_and_0xFF_expect_0xFF_Z0_N1(void){
	ClrStatus();
	uint8_t code[]={0x16,0x12};    //andwf 0x12
	memory[WREG]=0xFF;
	//*WREG=0xFF;
	memory[0x12]=0xFF;
	andwf(code);
	TEST_ASSERT_EQUAL(STATUS->Z,0);
	TEST_ASSERT_EQUAL(STATUS->N,1);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0xFF);
}
void test_andwf_0xFF_and_0x00_expect_0x00_Z1_N0(void){
	ClrStatus();
	uint8_t code[]={0x02,0x12};
	memory[WREG]=0x00;
	//*WREG=0x00;
	memory[0x12]=0xFF;
	andwf(code);
	TEST_ASSERT_EQUAL(STATUS->Z,1);
	TEST_ASSERT_EQUAL(STATUS->N,0);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x00);
}
void test_comf_0x80_expect_0x7F(void){
	uint8_t code[]={0x1E,0x12};   //comf 0x12,f
	memory[0x12]=0x80;
	comf(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x7F);
}
void test_iorwf_0x13_0x91_expect_0x93(void){
		uint8_t code[]={0x12,0x77};    //iorwf 0x77
		memory[0x77]=0x13;
		memory[WREG]=0x91;
		//*WREG=0x91;
		iorwf(code);
		TEST_ASSERT_EQUAL_HEX16(memory[0x77],0x93);
}
void test_bra_expect_PC_0x04(void){
	uint8_t code[]={0xD0,0x01};
	SET_PC(0x00);
	bra(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_bra_expect_PC_0x06(void){
	uint8_t code[]={0xD7,0xFE};
	SET_PC(0x08);
	bra(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x06);
}
void test_cpfseq_expect_PC_0x04(void){
  uint8_t code[]={0x62,0x01};
	CLEAR_PC();
  memory[0x01]=0x32;
  memory[WREG]=0x32;
	cpfseq(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_cpfseq_expect_PC_0x02(void){
  uint8_t code[]={0x62,0x01};
	CLEAR_PC();
  memory[0x01]=0x31;
  memory[WREG]=0x32;
	cpfseq(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_cpfsgt_expect_PC_0x04(void){
  uint8_t code[]={0x62,0x01};
	CLEAR_PC();
  memory[0x01]=0x32;
  memory[WREG]=0x31;
	cpfsgt(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_cpfsgt_expect_PC_0x02(void){
  uint8_t code[]={0x62,0x01};
	CLEAR_PC();
  memory[0x01]=0x32;
  memory[WREG]=0x32;
	cpfsgt(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_cpfslt_expect_PC_0x04(void){
  uint8_t code[]={0x62,0x01};
	CLEAR_PC();
  memory[0x01]=0x28;
  memory[WREG]=0x32;
	cpfslt(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_cpfslt_expect_PC_0x02(void){
  uint8_t code[]={0x62,0x01};
	CLEAR_PC();
  memory[0x01]=0x32;
  memory[WREG]=0x32;
	cpfslt(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_decf_expect_0xFF(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0;
  decf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x01],0xFF);
}
void test_decf_expect_0x01(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x02;
  decf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x01],0x01);
}
void test_decfsz_expect_PC_0x04(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x01;
  CLEAR_PC();
  decfsz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_decfsz_expect_PC_0x02(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x02;
  CLEAR_PC();
  decfsz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_dcfsnz_expect_PC_0x04(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x02;
  CLEAR_PC();
  dcfsnz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_dcfsnz_expect_PC_0x02(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x01;
  CLEAR_PC();
  dcfsnz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_incf_expect_0x77(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x76;
  incf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x01],0x77);
}
void test_incf_expect_0x00(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0xFF;
  incf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x01],0x00);
}
void test_incfsz_expect_PC_0x04(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0xFF;
  CLEAR_PC();
  incfsz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_incfsz_expect_PC_0x02(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x02;
  CLEAR_PC();
  incfsz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_infsnz_expect_PC_0x04(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x02;
  CLEAR_PC();
  infsnz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_infsnz_expect_PC_0x02(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0xFF;
  CLEAR_PC();
  infsnz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_movf_expect_0x99_in_0x12(void){
    uint8_t code[]={0x02,0x12};
    memory[0x12]=0x99;
    movf(code);
    TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x99);
    TEST_ASSERT_EQUAL_HEX16(STATUS->N,1);
    TEST_ASSERT_EQUAL_HEX16(STATUS->Z,0);
}
void test_mulwf_expect_0x21(void){
  uint8_t code[]={0x02,0x33};
  memory[0x33]=0x11;    //0x11*0x11=0x121
  memory[WREG]=0x11;     //take only 8bit =0x21
  mulwf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x33],0x21);
}
void test_negf_expect_0xC6(void){
  uint8_t code[]={0x02,0x33};
  memory[0x33]=0x3A;
  negf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x33],0xC6);
}
void test_rlcf_expect_0xCC(void){
  uint8_t code[]={0x02,0x33};
  memory[0x33]=0xE6;
  ClrStatus();
  rlcf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x33],0xCC);
  TEST_ASSERT_EQUAL_HEX16(STATUS->C,1);
}
void test_rlncf_expect_0xCC(void){
  uint8_t code[]={0x02,0x33};
  memory[0x33]=0xE6;
  ClrStatus();
  rlncf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x33],0xCD);
  TEST_ASSERT_EQUAL_HEX16(STATUS->C,0);
}
void test_rrcf_expect_0xCC(void){
  uint8_t code[]={0x02,0x33};
  memory[0x33]=0xD7;
  ClrStatus();
  rrcf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x33],0x6B);
  TEST_ASSERT_EQUAL_HEX16(STATUS->C,1);
}
void test_rrncf_expect_0xCC(void){
  uint8_t code[]={0x02,0x33};
  memory[0x33]=0xD7;
  ClrStatus();
  rrncf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x33],0xEB);
  TEST_ASSERT_EQUAL_HEX16(STATUS->C,0);
}
void test_swapf_expect_0xE8_to_0x8E(void){
	uint8_t code[]={0x02,0x28};
	memory[0x28]=0xE8;
	swapf(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x28],0x8E);
}
void test_swapf_expect_0x96_to_0x69(void){
	uint8_t code[]={0x02,0x28};
	memory[0x28]=0x96;
	swapf(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x28],0x69);
}
void test_tstfsz_expect_PC_0x04(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x00;
  CLEAR_PC();
  tstfsz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x04);
}
void test_tstfsz_expect_PC_0x02(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0x02;
  CLEAR_PC();
  tstfsz(code);
  TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x02);
}
void test_xorwf_expect_PC_0x02(void){
  uint8_t code[]={0x02,0x01};
  memory[0x01]=0xAF;
	memory[WREG]=0xB5;
  CLEAR_PC();
  xorwf(code);
  TEST_ASSERT_EQUAL_HEX16(memory[0x01],0x1A);
}
void test_addlw_expect_0x22(void){
	  uint8_t code[]={0x02,0x011};
		memory[WREG]=0x11;
		addlw(code);
		TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x22);
}
void test_andlw_expect_0x03(void){
	  uint8_t code[]={0x02,0x5F};
		memory[WREG]=0xA3;
		andlw(code);
		TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x03);
}
void test_mullw_expect_0x25(void){
	  uint8_t code[]={0x02,0xC4};
		memory[WREG]=0xE2;
		mullw(code);
		TEST_ASSERT_EQUAL_HEX16(memory[PRODH],0xAD);
		TEST_ASSERT_EQUAL_HEX16(memory[PRODL],0x08);
}
void test_sublw_expect_0x1(void){
	uint8_t code[]={0x02,0x02};
	memory[WREG]=0x01;
	sublw(code);
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x1);
	TEST_ASSERT_EQUAL_HEX16(STATUS->C,0x1);
	TEST_ASSERT_EQUAL_HEX16(STATUS->Z,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->N,0);
}
void test_sublw_expect_0x0(void){
	uint8_t code[]={0x02,0x02};
	memory[WREG]=0x02;
	sublw(code);
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->C,0x1);
	TEST_ASSERT_EQUAL_HEX16(STATUS->Z,1);
	TEST_ASSERT_EQUAL_HEX16(STATUS->N,0);
}
void test_sublw_expect_0xFF(void){
	uint8_t code[]={0x02,0x02};
	memory[WREG]=0x03;
	sublw(code);
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0xFF);
	TEST_ASSERT_EQUAL_HEX16(STATUS->C,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->Z,0);
	TEST_ASSERT_EQUAL_HEX16(STATUS->N,1);
}
void test_xorlw_expect_0x03(void){
	  uint8_t code[]={0x02,0xAF};
		memory[WREG]=0xB5;
		xorlw(code);
		TEST_ASSERT_EQUAL_HEX16(memory[WREG],0x1A);
}
void test_btg_expect(void){
	uint8_t code[]={0x08,0x02};
	memory[0x02]=0x75;
	btg(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x02],0x65);
}
void test_iorlw_expect(void){
	uint8_t code[]={0x02,0x35};
	memory[WREG]=0x9A;
	iorlw(code);
	TEST_ASSERT_EQUAL_HEX16(memory[WREG],0xBF);
}
void test_goto(void){
	uint8_t code[]={0xEF,0x76,
									0xF0,0x00,};
	goto1(code);
	TEST_ASSERT_EQUAL_HEX16(GET_PC(),0x76);
}
void test_subwfb_expect_0x00_C1_Z1(void){
	uint8_t code[]={0x02,0x12};    //subwfb 0x12,f
	memory[0x12]=0x1B;
	memory[WREG]=0x1A;
	STATUS->C=0;
	subwfb(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x00);
	TEST_ASSERT_EQUAL(STATUS->C,1);
	TEST_ASSERT_EQUAL(STATUS->Z,1);
}
void test_subwfb_expect_0xF5_C1_Z1(void){
	uint8_t code[]={0x02,0x12};    //subwfb 0x12,f
	memory[0x12]=0x03;
	memory[WREG]=0x0E;
	STATUS->C=1;
	subwfb(code);
	TEST_ASSERT_EQUAL_HEX16(memory[0x12],0x00);
	TEST_ASSERT_EQUAL(STATUS->C,1);
	TEST_ASSERT_EQUAL(STATUS->Z,1);
}
