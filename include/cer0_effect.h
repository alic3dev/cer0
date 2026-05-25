#ifndef __cer0_cer0_effect_h
#define __cer0_cer0_effect_h

#include <cer0_mix_mode.h>

struct cer0_effect;

typedef float (*cer0_effect_function_poll)(
  struct cer0_effect*,
  unsigned char,
  float
);

typedef void (*cer0_effect_function_destroy)(
  struct cer0_effect*
);

struct cer0_effect {
  cer0_effect_function_poll poll;
  cer0_effect_function_destroy destroy;

  enum cer0_mix_mode mix_mode;
  float mix;

  void* data;
};

void cer0_effect_initialize(
  struct cer0_effect*
);

float cer0_effect_poll(
  struct cer0_effect*,
  unsigned char,
  float
);

float cer0_effect_poll_default(
  struct cer0_effect*,
  unsigned char,
  float
);

void cer0_effect_destroy(
  struct cer0_effect*
);

void cer0_effect_destroy_default(
  struct cer0_effect*
);

#endif
