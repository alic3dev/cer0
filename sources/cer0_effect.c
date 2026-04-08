#include <cer0_effect.h>

#include <cer0_mix_mode.h>

#include <clic3_memory.h>

void cer0_effect_initialize(
  struct cer0_effect* cer0_effect
) {
  cer0_effect->poll = (
    cer0_effect_poll_default
  );

  cer0_effect->destroy = (
    cer0_effect_destroy_default
  );

  cer0_effect->mix_mode = (
    cer0_mix_mode_balance
  );

  cer0_effect->mix = (
    0.5f
  );

  cer0_effect->data = (
    0x00
  );
}

float cer0_effect_poll(
  struct cer0_effect* cer0_effect,
  unsigned char channel,
  float value_input
) {
  float value_wet = (
    cer0_effect->poll(
      cer0_effect,
      channel,
      value_input
    )
  );

  return (
    cer0_mix_mode_mix(
      value_input,
      value_wet,
      cer0_effect->mix,
      cer0_effect->mix_mode
    )
  );
}

float cer0_effect_poll_default(
  struct cer0_effect* cer0_effect,
  unsigned char channel,
  float value_input
) {
  return (
    value_input
  );
}

void cer0_effect_destroy(
  struct cer0_effect* cer0_effect
) {
  cer0_effect->destroy(
    cer0_effect
  );
}

void cer0_effect_destroy_default(
  struct cer0_effect* cer0_effect
) {
  clic3_memory_free(
    cer0_effect->data
  );
}
