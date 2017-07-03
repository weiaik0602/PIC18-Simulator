#ifndef _MAIN_H
#define _MAIN_H


typedef struct Data Data;
struct Data{
  unsigned short WREG;
  int f;
  int d;
  int a;
};


int Opcode(unsigned short code);

Data convertToOpCode(int x,unsigned short code);

#endif // _MAIN_H
