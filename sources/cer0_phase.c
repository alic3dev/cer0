#include <cer0_phase.h>
#include <cer0_constants.h>

float cer0_phase_get_increment(
  float sample_rate,
  float frequency
) {
  return (
    cer0_two_pi / sample_rate
  ) * frequency;
}

float cer0_phase_advance(
  float value_phase,
  float increment_phase
) {
  value_phase += increment_phase;

  if (value_phase >= cer0_two_pi) {
    value_phase -= cer0_two_pi;
  }

  if (value_phase < 0.0f) {
    value_phase += cer0_two_pi;
  }

  return value_phase;
}
