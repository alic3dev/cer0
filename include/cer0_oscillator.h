#ifndef __cer0_oscillator_h
#define __cer0_oscillator_h

#import <cer0_phase.h>
#import <cer0_signal.h>

struct cer0_oscillator {
  float amplitude;
  float offset_frequency;
  float pan;

  struct cer0_phase phase;

  enum cer0_signal signal;
  cer0_signal_function signal_function;
};

void cer0_oscillator_initialize(
  struct cer0_oscillator*,
  float,
  float,
  enum cer0_signal
);

void cer0_oscillator_frequency_set(
  struct cer0_oscillator*,
  float
);

void cer0_oscillator_offset_frequency_set(
  struct cer0_oscillator*,
  float
);

void cer0_oscillator_frequency_with_offset_set(
  struct cer0_oscillator*,
  float,
  float
);

void cer0_oscillator_sample_rate_set(
  struct cer0_oscillator*,
  float
);

void cer0_oscillator_signal_set(
  struct cer0_oscillator*,
  enum cer0_signal
);

float cer0_oscillator_poll(
  struct cer0_oscillator*
);

void cer0_oscillator_poll_stereo(
  struct cer0_oscillator*,
  float[
    0x02
  ]
);

#endif
