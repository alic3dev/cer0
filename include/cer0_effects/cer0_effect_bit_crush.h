#ifndef __cer0_cer0_effects_cer0_effect_bit_crush_h
#define __cer0_cer0_effects_cer0_effect_bit_crush_h

#include <cer0_effect.h>

enum cer0_effect_bit_crush_mode {
  cer0_effect_bit_crush_mode_bits  = 0x00,
  cer0_effect_bit_crush_mode_value = 0x01
};
struct cer0_effect_bit_crush_data {
  unsigned char bits;
  
  unsigned char mode;
  
  unsigned int value_maximum;

  float range;
};

void cer0_effect_bit_crush_initialize(
  struct cer0_effect*,
  unsigned char
);

void cer0_effect_bit_crush_mode_set(
  struct cer0_effect*,
  unsigned char
);

void cer0_effect_bit_crush_bits_set(
  struct cer0_effect*,
  unsigned char
);

float cer0_effect_bit_crush_poll(
  struct cer0_effect*,
  unsigned char,
  float
);

#endif
