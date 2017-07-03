#include "Main.h"
//#include "mov.h"
#include <stdint.h>
#include "Functions.h"



//typedef unsigned int uint32_t;



int Opcode(unsigned short code){
  int opcode=code>>8;
  //return opcode;
  Data data;
  data=convertToOpCode(opcode,code);
  return data.WREG; 
  
}

Data convertToOpCode(int x,unsigned short code){
  Data data;
  switch(x){
    case 0x000E:
      data=movlw(code);
    break;
    
    default:
      break;
      
      
  }
  return data;
  }

