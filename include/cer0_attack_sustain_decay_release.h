#ifndef __cer0_cer0_attack_sustain_decay_release_h
#define __cer0_cer0_attack_sustain_decay_release_h

#include <cer0_ramp.h>

struct cer0_attack_sustain_decay_release_parameters {
  float attack;
  float sustain;
  float decay;
  float release;

  float amplitude_initial;
  float amplitude_attack;
  float amplitude_sustain;
  float amplitude_decay;
  float amplitude_release;

  cer0_ramp_function_poll poll_ramp_attack;
  cer0_ramp_function_poll poll_ramp_sustain;
  cer0_ramp_function_poll poll_ramp_decay;
  cer0_ramp_function_poll poll_ramp_release;
};

void cer0_attack_sustain_decay_release_parameters_initialize(
  struct cer0_attack_sustain_decay_release_parameters*
);

float cer0_attack_sustain_decay_release_poll(
  struct cer0_attack_sustain_decay_release_parameters*,
  float
);
#endif
