#include <malloc.h>
#include <stdarg.h>
#include "Exception.h"
#include "CException.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include "token.h"

void add(int a ,int b){
  a+b;
}
void throwException(int errorCode, char *message, ...) {
  va_list args;
  char *buffer;
  int length;
  Exception *e;

  va_start(args, message);
  e = malloc(sizeof(Exception));

  length = vsnprintf(buffer, 0, message, args);
  buffer = malloc(length + 1);
  vsnprintf(buffer, length + 1, message, args);

  e->msg = buffer;
  e->errorCode = errorCode;
  //e->data = data;

  Throw(e);
}

void freeException(Exception *e) {
  if(e) {
    if(e->msg)
      free(e->msg);
    free(e);
  }
}

void dumpException(Exception *e) {
  printf("%s \n", e->msg);
}
