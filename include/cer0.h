#ifndef __CER0_H
#define __CER0_H

#include "cer0_constants.h"
#include "cer0_phase.h"
#include "cer0_signals.h"

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
