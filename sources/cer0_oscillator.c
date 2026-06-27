#include <cer0_oscillator.h>

#include <cer0_amplitude.h>
#include <cer0_pan.h>
#include <cer0_phase.h>
#include <cer0_signal.h>

void cer0_oscillator_initialize(
  struct cer0_oscillator* oscillator,
  float sample_rate,
  float frequency,
  enum cer0_signal signal
) {
  oscillator->amplitude = (
    cer0_default_amplitude
  );

  oscillator->offset_frequency = (
    0x00
  );

  oscillator->pan = (
    0x00
  );

  cer0_phase_initialize(
    &oscillator->phase,
    sample_rate,
    (
      frequency +
      oscillator->offset_frequency
    )
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
    (
      frequency +
      oscillator->offset_frequency
    )
  );
}

void cer0_oscillator_offset_frequency_set(
  struct cer0_oscillator* cer0_oscillator,
  float offset_frequency
) {
  cer0_oscillator->offset_frequency = (
    offset_frequency
  );

  cer0_phase_frequency_set(
    &cer0_oscillator->phase,
    (
      cer0_oscillator->phase.frequency +
      cer0_oscillator->offset_frequency
    )
  );
}

void cer0_oscillator_frequency_with_offset_set(
  struct cer0_oscillator* cer0_oscillator,
  float frequency,
  float offset_frequency
) {
  cer0_oscillator->offset_frequency = (
    offset_frequency
  );

  cer0_oscillator_frequency_set(
    cer0_oscillator,
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
  struct cer0_oscillator* cer0_oscillator
) {
  cer0_phase_poll(
    &cer0_oscillator->phase
  );

  return (
    cer0_oscillator->signal_function(
      cer0_oscillator->phase.value
    ) *
    cer0_oscillator->amplitude
  );
}

void cer0_oscillator_poll_stereo(
  struct cer0_oscillator* cer0_oscillator,
  float result[
    0x02
  ]
) {
  cer0_pan_apply_stereo(
    cer0_oscillator_poll(
      cer0_oscillator
    ),
    cer0_oscillator->pan,
    result
  );
}
