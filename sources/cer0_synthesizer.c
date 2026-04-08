#include <cer0_synthesizer.h>
#include <cer0_amplitude.h>
#include <cer0_oscillator.h>
#include <cer0_signal.h>

#include <clic3_memory.h>

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
  synthesizer->oscillators = (
    clic3_memory_allocate_raw(
      sizeof(
        struct cer0_oscillator
      ) *
      synthesizer->length_oscillators
    )
  );

  synthesizer->sample_rate = (
    sample_rate
  );

  synthesizer->length_effects = (
    0x00
  );

  synthesizer->effects = (
    clic3_memory_allocate_raw(
      sizeof(
        struct cer0_effect*
      ) *
      synthesizer->length_effects
    )
  );}

void cer0_synthesizer_oscillator_add(
  struct cer0_synthesizer* synthesizer,
  enum cer0_signal signal
) {
  synthesizer->length_oscillators = (
    synthesizer->length_oscillators + 1
  );

  clic3_memory_reallocate_raw(
    &synthesizer->oscillators,
    (
      sizeof(
        struct cer0_oscillator
      ) *
      synthesizer->length_oscillators
    )
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

void cer0_synthesizer_effect_add(
  struct cer0_synthesizer* cer0_synthesizer,
  struct cer0_effect* cer0_effect
) {
  cer0_synthesizer->length_effects = (
    cer0_synthesizer->length_effects +
    0x01
  );

  clic3_memory_reallocate_raw(
    &cer0_synthesizer->effects,
    (
      sizeof(
        struct cer0_effect*
      ) *
      cer0_synthesizer->length_effects
    )
  );

  cer0_synthesizer->effects[
    cer0_synthesizer->length_effects -
    0x01
  ] = (
    cer0_effect
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

  for (
    unsigned int index_effect = (
      0x00
    );
    (
      index_effect <
      synthesizer->length_effects
    );
    ++index_effect
  ) {
    value_output = (
      cer0_effect_poll(
        synthesizer->effects[
          index_effect
        ],
        0x00,
        value_output
      )
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
  clic3_memory_free_raw(
    synthesizer->oscillators
  );
}
