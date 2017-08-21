#ifndef _SIMULATOR_H
#define _SIMULATOR_H
#include <stdint.h>


typedef struct Simulator Simulator;

struct Simulator{
  void (*execute)(uint8_t *code);
};
void simulateInstruction(int numberOfInstruction);
void simulateAll();
#endif // _SIMULATOR_H
