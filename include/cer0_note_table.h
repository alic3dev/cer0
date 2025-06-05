#ifndef __cer0_note_table_h
#define __cer0_note_table_h

#define cer0_steps_in_octave 12
#define cer0_default_steps_notes cer0_steps_in_octave

float* cer0_note_table_stepped_create(
  char,
  char,
  float,
  unsigned char
);

float* cer0_note_table_create(
  char,
  char,
  float
);

unsigned int cer0_note_table_stepped_length(
  char,
  char,
  unsigned char
);

unsigned int cer0_note_table_length(
  char,
  char
);

#endif
