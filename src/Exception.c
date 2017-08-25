#include "GlobalVariable.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include "Exception.h"
#include "CException.h"



Exception *createException(char *msg, int errorCode){
  Exception *e = malloc(sizeof(Exception));
  e -> msg = msg;
  e -> errorCode = errorCode;
  return e;
}

void throwException(int errorCode, void *data, char *message, ...) {
  va_list args;
  char *buffer;
  int length;
  Exception *e;

  va_start(args, message);
  e = malloc(sizeof(Exception));

  length = vsnprintf(buffer, 0, message, args);
  buffer = malloc(length + 1);
  vsnprintf(buffer, length, message, args);

  e->msg = buffer;
  e->errorCode = errorCode;
  e->data = data;

  Throw(e);
}

void freeException(Exception *e) {
  if(e) {
    if(e->msg)
      free(e->msg);
    free(e);
  }
}
void freeException1(Exception *e){
  free(e);
}


void dumpException(Exception *e){
  printf ("%s (opcode = 0x%02x)\n", e->msg, e->errorCode);
  printf("%s\n","This program will be stopped!!!" );
  printf("-----------------------------------------------------------------");
}
