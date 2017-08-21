#include "GlobalVariable.h"
#include <stdint.h>

uint8_t memory[4*KB];
uint8_t flash[2*MB];
uint8_t tableBuffer[8];
int enableFlashWrite=0;
