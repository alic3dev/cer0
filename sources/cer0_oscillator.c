#include <cer0_oscillator.h>
#include <cer0_amplitude.h>
#include <cer0_phase.h>
#include <cer0_signal.h>

void cer0_oscillator_initialize(
  struct cer0_oscillator* oscillator,
  float sample_rate,
  float frequency,
  enum cer0_signal signal
) {
  oscillator->amplitude = cer0_default_amplitude;

  cer0_phase_initialize(
    &oscillator->phase,
    sample_rate,
    frequency
  );

  cer0_oscillator_signal_set(
    oscillator,
    signal
  );
}

void cer0_oscillator_frequency_set(
  struct cer0_oscillator* oscillator,
  float frequency
) {
  cer0_phase_frequency_set(
    &oscillator->phase,
    frequency
  );
}

void cer0_oscillator_sample_rate_set(
  struct cer0_oscillator* oscillator,
  float sample_rate
) {
  cer0_phase_sample_rate_set(
    &oscillator->phase,
    sample_rate
  );
}

void cer0_oscillator_signal_set(
  struct cer0_oscillator* oscillator,
  enum cer0_signal signal
) {
  oscillator->signal = signal;
  oscillator->signal_function = (
    cer0_signal_function_lookup[
      oscillator->signal
    ]
  );
}

float cer0_oscillator_poll(
  struct cer0_oscillator* oscillator
) {
  cer0_phase_poll(
    &oscillator->phase
  );

  return (
    oscillator->signal_function(
      oscillator->phase.value
    ) *
    oscillator->amplitude
  );
}
