#include <cer0_synthesizer.h>
#include <cer0_amplitude.h>
#include <cer0_oscillator.h>
#include <cer0_signal.h>

#include <stdlib.h>

#define for_oscillators\
  for (\
    unsigned int index_oscillator = 0;\
    index_oscillator < synthesizer->length_oscillators;\
    ++index_oscillator\
  )\

void cer0_synthesizer_initialize(
  struct cer0_synthesizer* synthesizer,
  float sample_rate
) {
  synthesizer->amplitude = cer0_default_amplitude;
  synthesizer->frequency = 0;

  synthesizer->length_oscillators = 0;
  synthesizer->oscillators = malloc(
    sizeof(struct cer0_oscillator) *
    synthesizer->length_oscillators
  );

  synthesizer->sample_rate = sample_rate;
}

void cer0_synthesizer_oscillator_add(
  struct cer0_synthesizer* synthesizer,
  enum cer0_signal signal
) {
  synthesizer->length_oscillators = (
    synthesizer->length_oscillators + 1
  );

  synthesizer->oscillators = realloc(
    synthesizer->oscillators,
    sizeof(struct cer0_oscillator) *
    synthesizer->length_oscillators
  );

  cer0_oscillator_initialize(
    &synthesizer->oscillators[
      synthesizer->length_oscillators -
      1
    ],
    synthesizer->sample_rate,
    synthesizer->frequency,
    signal
  );
}

void cer0_synthesizer_frequency_set(
  struct cer0_synthesizer* synthesizer,
  float frequency
) {
  synthesizer->frequency = frequency;

  for_oscillators {
    cer0_synthesizer_oscillator_frequency_set(
      synthesizer,
      index_oscillator,
      synthesizer->frequency
    );
  }
}

void cer0_synthesizer_oscillator_frequency_set(
  struct cer0_synthesizer* synthesizer,
  unsigned int index_oscillator,
  float frequency
) {
  cer0_oscillator_frequency_set(
    &synthesizer->oscillators[
      index_oscillator
    ],
    frequency
  );
}

void cer0_synthesizer_signal_set(
  struct cer0_synthesizer* synthesizer,
  enum cer0_signal signal
) {
  for_oscillators {
    cer0_synthesizer_oscillator_signal_set(
      synthesizer,
      index_oscillator,
      signal
    );
  }
}

void cer0_synthesizer_oscillator_signal_set(
  struct cer0_synthesizer* synthesizer,
  unsigned int index_oscillator,
  enum cer0_signal signal
) {
  cer0_oscillator_signal_set(
    &synthesizer->oscillators[
      index_oscillator
    ],
    signal
  );
}

void cer0_synthesizer_sample_rate_set(
  struct cer0_synthesizer* synthesizer,
  float sample_rate
) {
  synthesizer->sample_rate = sample_rate;

  for_oscillators {
    cer0_oscillator_sample_rate_set(
      &synthesizer->oscillators[
        index_oscillator
      ],
      synthesizer->sample_rate
    );
  }
}

float cer0_synthesizer_poll(
  struct cer0_synthesizer* synthesizer
) {
  float value_output = 0.0f;

  for_oscillators {
    value_output = (
      value_output +
      cer0_oscillator_poll(
        &synthesizer->oscillators[
          index_oscillator
        ]
      ) /
      (float) synthesizer->length_oscillators
    );
  }

  return (
    value_output *
    synthesizer->amplitude
  );
}

void cer0_synthesizer_destroy(
  struct cer0_synthesizer* synthesizer
) {
  free(
    synthesizer->oscillators
  );
}
