#ifndef __cer0_synthesizer_h
#define __cer0_synthesizer_h

#include <cer0_attack_sustain_decay_release.h>
#include <cer0_effect.h>
#include <cer0_oscillator.h>
#include <cer0_signal.h>

struct cer0_synthesizer {
  float amplitude;
  float frequency;
  float pan;

  unsigned int length_oscillators;
  struct cer0_oscillator* oscillators;

  struct cer0_effect** effects;
  unsigned int length_effects;

  struct cer0_attack_sustain_decay_release_parameters attack_sustain_decay_release_parameters;

  unsigned long int length_attack_sustain_decay_release;
  unsigned long int index_attack_sustain_decay_release;

  float sample_rate;
};

void cer0_synthesizer_initialize(
  struct cer0_synthesizer*,
  float
);

void cer0_synthesizer_oscillator_add(
  struct cer0_synthesizer*,
  enum cer0_signal
);

struct cer0_effect* cer0_synthesizer_effect_add(
  struct cer0_synthesizer*
);

void cer0_synthesizer_frequency_set(
  struct cer0_synthesizer*,
  float
);

void cer0_synthesizer_frequency_play(
  struct cer0_synthesizer*,
  float
);

void cer0_synthesizer_oscillator_frequency_set(
  struct cer0_synthesizer*,
  unsigned int,
  float
);

void cer0_synthesizer_signal_set(
  struct cer0_synthesizer*,
  enum cer0_signal
);

void cer0_synthesizer_oscillator_signal_set(
  struct cer0_synthesizer*,
  unsigned int,
  enum cer0_signal
);

float cer0_synthesizer_poll(
  struct cer0_synthesizer*
);

void cer0_synthesizer_poll_stereo(
  struct cer0_synthesizer*,
  float[
    0x02
  ]
);

void cer0_synthesizer_destroy(
  struct cer0_synthesizer*
);

#endif
