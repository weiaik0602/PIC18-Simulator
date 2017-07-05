#ifndef _MAIN_H
#define _MAIN_H
#include <stdint.h>



typedef struct Data Data;
struct Data{
  unsigned short WREG;
  int f;
  int d;
  int a;
};


uint32_t Opcode(uint32_t code);

Data convertToOpCode(int x,unsigned short code);

#endif // _MAIN_H
