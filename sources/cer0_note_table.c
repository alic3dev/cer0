#include <cer0_note_table.h>
#include <cer0_octave_range.h>

#include <math.h>
#include <stdlib.h>

float* cer0_note_table_stepped_create(
  char octave_starting,
  char octave_ending,
  float frequency,
  unsigned char steps_notes
) {
  if (octave_ending < octave_starting) {
    unsigned char octave_temporary_swap_value = octave_ending;
    octave_ending = octave_starting;
    octave_starting = octave_temporary_swap_value;
  }

  static float* note_table;

  note_table = malloc(
    sizeof(float) * cer0_note_table_stepped_length(
      octave_starting,
      octave_ending,
      steps_notes
    )
  );

  for (
    char index_octave = octave_starting;
    index_octave <= octave_ending;
    ++index_octave
  ) {
    unsigned char offset_octave_table = (index_octave - octave_starting) * steps_notes;

    for (
      unsigned char index_note = 0;
      index_note < steps_notes;
      ++index_note
    ) {
      note_table[offset_octave_table + index_note] = (
          powf(
            2.0f,
            (
              -57.0f + (float)(
                (((float)index_note) * (((float)cer0_steps_in_octave) / ((float)steps_notes))) +
                (((float)index_octave) * ((float)cer0_steps_in_octave))
              )
            )  / ((float)cer0_steps_in_octave)
          ) * frequency
      );
    }
  }

  return note_table;
}

float* cer0_note_table_create(
  char octave_starting,
  char octave_ending,
  float frequency
) {
  return cer0_note_table_stepped_create(
    octave_starting,
    octave_ending,
    frequency,
    cer0_default_steps_notes
  );
}

unsigned int cer0_note_table_stepped_length(
  char octave_starting,
  char octave_ending,
  unsigned char steps_notes
) {
  return cer0_octave_range_get(
    octave_starting,
    octave_ending
  ) * steps_notes;
}

unsigned int cer0_note_table_length(
  char octave_starting,
  char octave_ending
) {
  return cer0_note_table_stepped_length(
    octave_starting,
    octave_ending,
    cer0_default_steps_notes
  );
}
