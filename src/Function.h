#ifndef _FUNCTION_H
#define _FUNCTION_H


//functions
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
void bnz(uint8_t *code);
void bz(uint8_t *code);
void bov(uint8_t *code);
void bnov(uint8_t *code);
void addwfc(uint8_t *code);
void andwf(uint8_t *code);
void comf(uint8_t *code);
void iorwf(uint8_t *code);
void tblrd();
void tblrdposi();
void tblrdposd();
void tblrdprei();
void tblwt();
void tblwtposi();
void tblwtposd();
void tblwtprei();
void bra(uint8_t *code);


#endif // _FUNCTION_H
