#ifndef _SIMULATOR_H
#define _SIMULATOR_H
#include <stdint.h>


typedef struct Simulator Simulator;

struct Simulator{
  void (*execute)(uint8_t *code);
};
void Simulate(int size);
#endif // _SIMULATOR_H
