#include <cer0_phase.h>
#include <cer0_constants.h>

void cer0_phase_initialize(
  struct cer0_phase* phase,
  float sample_rate,
  float frequency
) {
  phase->frequency = frequency;
  phase->sample_rate = sample_rate;

  cer0_phase_increment_set(phase);

  phase->value = 0;
}

void cer0_phase_poll(
  struct cer0_phase* phase
) {
  phase->value = cer0_phase_advance(
    phase->value,
    phase->increment
  );
}

void cer0_phase_frequency_set(
  struct cer0_phase* phase,
  float frequency
) {
  phase->frequency = frequency;

  cer0_phase_increment_set(phase);
}

void cer0_phase_sample_rate_set(
  struct cer0_phase* phase,
  float sample_rate
) {
  phase->sample_rate = sample_rate;

  cer0_phase_increment_set(phase);
}

void cer0_phase_increment_set(
  struct cer0_phase* phase
) {
  phase->increment = cer0_phase_get_increment(
    phase->sample_rate,
    phase->frequency
  );
}

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
