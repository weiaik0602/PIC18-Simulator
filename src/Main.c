#include "Main.h"
//#include "mov.h"
#include <stdint.h>
#include "Functions.h"

volatile uint32_t *WREG = (volatile uint32_t *)0xFE8;






uint32_t Opcode(uint32_t code){
  int opcode=code>>8;

  //return opcode;
  //Data data;
  //data=convertToOpCode(opcode,code);
  //return WREG=0x2F;
  //WREG=0x2F;
  return WREG; 
  
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

