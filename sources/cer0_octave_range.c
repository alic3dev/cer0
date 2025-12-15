#include <cer0_octave_range.h>

unsigned int cer0_octave_range_get(
  char octave_starting,
  char octave_ending
) {
  if (
    octave_ending < octave_starting
  ) {
    return (
      octave_starting -
      octave_ending +
      1
    );
  }

  return (
    octave_ending -
    octave_starting +
    1
  );
}
