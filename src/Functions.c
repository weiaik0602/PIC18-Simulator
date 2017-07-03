#include "Functions.h"




Data movlw(unsigned short code){
  Data data;
  data.WREG=(code&0x00FF);
  return data;
}