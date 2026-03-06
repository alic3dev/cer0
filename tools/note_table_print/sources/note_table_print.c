#include <note_table_print.h>

#include <cer0.h>

#include <clic3_memory.h>

#include <stdio.h>

int main(
  int argc,
  char** argv
) {
  if (argc < 4 || argc > 5) {
    fprintf(
      stderr,
      "usage: note_table_print #octave_starting #octave_ending #frequency #?steps_notes\n"
    );

    return 1;
  }

  char octave_starting = atoi(
    argv[1]
  );

  char octave_ending = atoi(
    argv[2]
  );

  float frequency = atof(
    argv[3]
  );

  unsigned char steps_notes;

  if (argc == 5) {
    steps_notes = atoi(
      argv[4]
    );
  } else {
    steps_notes = cer0_default_steps_notes;
  }

  float* note_table = cer0_note_table_stepped_create(
    octave_starting,
    octave_ending,
    frequency,
    steps_notes
  );

  unsigned int length_note_table = cer0_note_table_stepped_length(
    octave_starting,
    octave_ending,
    steps_notes
  );

  printf("[\n");

  for (
    unsigned int index_note = 0;
    index_note < length_note_table;
    ++index_note
  ) {
    if (index_note != 0) {
      printf(",\n");
    }

    printf(
      "  {\n"
      "    \"octave\": %i,\n"
      "    \"note\": %i,\n"
      "    \"frequency\": %f\n"
      "  }",
      octave_starting + (index_note / steps_notes),
      index_note % steps_notes,
      note_table[index_note]
    );
  }

  printf("\n]\n");

  clic3_memory_free_raw(
    note_table
  );

  return 0;
}
