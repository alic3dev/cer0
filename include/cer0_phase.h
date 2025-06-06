#ifndef __cer0_phase_h
#define __cer0_phase_h

struct cer0_phase {
  float frequency;
  float increment;
  float sample_rate;
  float value;
};

void cer0_phase_initialize(
  struct cer0_phase*,
  float,
  float
);

void cer0_phase_poll(
  struct cer0_phase*
);

void cer0_phase_frequency_set(
  struct cer0_phase*,
  float
);

void cer0_phase_sample_rate_set(
  struct cer0_phase*,
  float
);

void cer0_phase_increment_set(
  struct cer0_phase*
);

float cer0_phase_get_increment(
  float,
  float
);

float cer0_phase_advance(
  float,
  float
);

#endif
