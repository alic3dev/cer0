#ifndef __cer0_cer0_effects_cer0_effect_distortion_h
#define __cer0_cer0_effects_cer0_effect_distortion_h

#include <cer0_effect.h>

struct cer0_effect_distortion_data {
  float gain;
  float noise;
};

void cer0_effect_distortion_initialize(
  struct cer0_effect*
);

float cer0_effect_distortion_poll(
  struct cer0_effect*,
  unsigned char,
  float
);

#endif
