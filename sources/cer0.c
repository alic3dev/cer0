#include "cer0.h"

#include <math.h>
#include <stdlib.h>

float* cer0_create_note_table(
  unsigned char octave_starting,
  unsigned char octave_ending,
  float frequency
) {
  unsigned char octave_range = (octave_ending - octave_starting) + 1;

  static float* note_table;

  note_table = malloc
    (sizeof(float) * octave_range * 12
  );

  for (
    unsigned char i = octave_starting;
    i <= octave_ending;
    ++i
  ) {
    unsigned char offset_octave = (i - octave_starting) * 12;

    for (
      unsigned char x = 0;
      x < 12;
      ++x
    ) {
      float offset_note = -57.0f + (float)(x);

      note_table[offset_octave + x] = (
          powf(
            2.0f,
            (offset_note + (float)(offset_octave)) / 12.0f
          ) * frequency
      );
    }
  }

  return note_table;
}

unsigned int cer0_sizeof_note_table(
  unsigned char octave_starting,
  unsigned char octave_ending
) {
  return (octave_ending - octave_starting) * 12;
}
