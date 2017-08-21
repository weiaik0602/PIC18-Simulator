#ifndef _GLOBALVARIABLE_H
#define _GLOBALVARIABLE_H
#include <stdint.h>


extern uint8_t memory[];
extern uint8_t flash[];
extern uint8_t tableBuffer[];
extern int enableFlashWrite;



#define KB 1024
#define MB 1048576
#define SET        1
#define CLEAR      0
#define C_Bit      0
#define OV_Bit     3
#define Z_Bit      2

uint8_t PCL;
uint8_t PCLATH;
uint8_t PCLATU;
uint8_t TBLPTRL;
uint8_t TBLPTRH;
uint8_t TBLPTRU;
//defining some number


//macros
#define GET_TBLPTR()          (TBLPTRL|(TBLPTRH<<8)|(TBLPTRU<<16))
#define GET_PC()              (PCL|(PCLATH<<8)|(PCLATU<<16))
#define ADD_PC(step)          (SET_PC(GET_PC() + (step) * 2))

//address of SFR
#define STATUS    ((StatusReg*)&memory[0xFD8])
#define WREG      0xFE8
#define BSR       0xFE0
#define TABLAT    0xFF5
#define EECON2    0xFA7

//structure
typedef struct StatusReg StatusReg;
struct StatusReg{
  uint8_t C:1;
  uint8_t DC:1;
  uint8_t Z:1;
  uint8_t OV:1;
  uint8_t N:1;
};

#endif // _GLOBALVARIABLE_H
