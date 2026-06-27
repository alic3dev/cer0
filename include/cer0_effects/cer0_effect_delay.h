#ifndef __cer0_effects_cer0_effect_delay_h
#define __cer0_effects_cer0_effect_delay_h

#include <cer0_effect.h>

struct cer0_effect_delay_data {
  float** frames_buffer;
  unsigned int length_frames_buffer;

  unsigned int* index_frames_buffer;

  unsigned char length_channels;

  float decay;
};

void cer0_effect_delay_initialize(
  struct cer0_effect*,
  unsigned char
);

void cer0_effect_delay_length_frames_buffer_set(
  struct cer0_effect*,
  unsigned int
);

float cer0_effect_delay_poll(
  struct cer0_effect*,
  unsigned char,
  float
);

void cer0_effect_delay_destroy(
  struct cer0_effect*
);

#endif
