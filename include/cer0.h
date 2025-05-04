#ifndef cer0_h
#define cer0_h

#include "constants.h"
#include "phase.h"
#include "signals.h"

float *createNoteTable(
  unsigned char,
  unsigned char,
  float
);

unsigned int sizeofNoteTable(
  unsigned char,
  unsigned char
);

#endif
