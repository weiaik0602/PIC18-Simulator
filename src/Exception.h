#ifndef Exception_H
#define Exception_H
#include "error.h"
#include "CExceptionConfig.h"

typedef struct Exception Exception;
typedef Exception* ExceptionPtr;
struct Exception {
  char *msg;
  uint16_t  errorCode;
  void *data;
};

Exception *createException(char *msg, int errorCode);
void freeException(Exception *e);
void dumpException(Exception *e);
void freeException1(Exception *e);
void dumpErrorMessage(Exception *e, int lineNo) ;
void throwException(int errorCode, void *data, char *message, ...);
#endif // Exception_H
