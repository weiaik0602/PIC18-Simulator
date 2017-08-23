#ifndef _SIMULATOR_H
#define _SIMULATOR_H
#include <stdint.h>
#include "token.h"
#include "error.h"


typedef struct Simulator Simulator;

struct Simulator{
  void (*execute)(uint8_t *code);
};
void simulateInstruction(int numberOfInstruction);
void simulateAll();
void printErrorMessage(uint16_t opcode);
void simulateInstruction1(int numberOfInstruction);
#endif // _SIMULATOR_H
