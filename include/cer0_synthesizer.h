#ifndef __cer0_synthesizer_h
#define __cer0_synthesizer_h

#include <cer0_oscillator.h>
#include <cer0_signal.h>

struct cer0_synthesizer {
  float amplitude;
  float frequency;

  unsigned int length_oscillators;
  struct cer0_oscillator* oscillators;

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

void cer0_synthesizer_frequency_set(
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

void cer0_synthesizer_destroy(
  struct cer0_synthesizer*
);

#endif
