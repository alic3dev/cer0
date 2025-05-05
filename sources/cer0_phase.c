#include "cer0_phase.h"

#include <math.h>
#include <stdio.h>

float cer0_phase_get_increment(
  float sample_rate,
  float frequency
) {
  return ((M_PI * 2.0f) / sample_rate) * frequency;
}

float cer0_phase_advance(
  float value_phase,
  float increment_phase
) {
  value_phase += increment_phase;

  if (value_phase >= CER0_TWO_PI) {
    value_phase -= CER0_TWO_PI;
  }

  if (value_phase < 0.0f) {
    value_phase += CER0_TWO_PI;
  }

  return value_phase;
}
