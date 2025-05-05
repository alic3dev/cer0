#ifndef cer0_h
#define cer0_h

#include "constants.h"
#include "phase.h"
#include "signals.h"

float *cer0_create_note_table(
  unsigned char,
  unsigned char,
  float
);

unsigned int cer0_sizeof_note_table(
  unsigned char,
  unsigned char
);

#endif
