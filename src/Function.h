#ifndef _FUNCTION_H
#define _FUNCTION_H


//functions
void tblrd();
void tblrdposi();
void tblrdposd();
void tblrdprei();
void tblwt();
void tblwtposi();
void tblwtposd();
void tblwtprei();
void daw();
void zero(uint8_t *code);
void movlb(uint8_t *code);
void movlw(uint8_t *code);
void movwf(uint8_t *code);
void addwf(uint8_t *code);
void subwf(uint8_t *code);
void bcf(uint8_t *code);
void bsf(uint8_t *code);
void setf(uint8_t *code);
void clrf(uint8_t *code);
void btfss(uint8_t *code);
void btfsc(uint8_t *code);
void nop(uint8_t *code);
void movff(uint8_t *code);
void bc(uint8_t *code);
void bnc(uint8_t *code);
void bn(uint8_t *code);
void bnn(uint8_t *code);
void bnz(uint8_t *code);
void bz(uint8_t *code);
void bov(uint8_t *code);
void bnov(uint8_t *code);
void addwfc(uint8_t *code);
void andwf(uint8_t *code);
void comf(uint8_t *code);
void iorwf(uint8_t *code);
void bra(uint8_t *code);
void cpfseq(uint8_t *code);
void cpfsgt(uint8_t *code);
void cpfslt(uint8_t *code);
void decf(uint8_t *code);
void decfsz(uint8_t *code);
void dcfsnz(uint8_t *code);
void incf(uint8_t *code);
void incfsz(uint8_t *code);
void infsnz(uint8_t *code);
void movf(uint8_t *code);
void mulwf(uint8_t *code);
void negf(uint8_t *code);
void rlcf(uint8_t *code);
void rlncf(uint8_t *code);
void rrcf(uint8_t *code);
void rrncf(uint8_t *code);
void swapf(uint8_t *code);
void tstfsz(uint8_t *code);
void xorwf(uint8_t *code);
void addlw(uint8_t *code);
void andlw(uint8_t *code);
void mullw(uint8_t *code);
void sublw(uint8_t *code);
void xorlw(uint8_t *code);
void btg(uint8_t *code);
void iorlw(uint8_t *code);
void goto1(uint8_t *code);
#endif // _FUNCTION_H
