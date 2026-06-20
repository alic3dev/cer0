#ifndef __cer0_cer0_effects_cer0_effect_attack_sustain_decay_release_h
#define __cer0_cer0_effects_cer0_effect_attack_sustain_decay_release_h

#include <cer0_effect.h>

void cer0_effect_attack_sustain_decay_release_initialize(
  struct cer0_effect*
);

float cer0_effect_attack_sustain_decay_release_poll(
  struct cer0_effect*,
  unsigned char,
  float
);

#endif
