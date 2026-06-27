#include <cer0_synthesizer.h>

#include <cer0_amplitude.h>
#include <cer0_attack_sustain_decay_release.h>
#include <cer0_oscillator.h>
#include <cer0_pan.h>
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
  synthesizer->amplitude = (
    cer0_default_amplitude
  );

  synthesizer->frequency = (
    0x00
  );

  synthesizer->pan = (
    0x00
  );

  synthesizer->length_oscillators = (
    0x00
  );

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
  );

  synthesizer->length_attack_sustain_decay_release = (
    0x00
  );

  synthesizer->index_attack_sustain_decay_release = (
    0x00
  );

  cer0_attack_sustain_decay_release_parameters_initialize(
    &synthesizer->attack_sustain_decay_release_parameters
  );
}

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
      0x01
    ],
    synthesizer->sample_rate,
    synthesizer->frequency,
    signal
  );
}

struct cer0_effect* cer0_synthesizer_effect_add(
  struct cer0_synthesizer* cer0_synthesizer
) {
  unsigned int index_effect = (
    cer0_synthesizer->length_effects
  );

  cer0_synthesizer->length_effects = (
    cer0_synthesizer->length_effects +
    0x01
  );

  clic3_memory_reallocate_raw(
    &cer0_synthesizer->effects,
    (
      sizeof(
        void*
      ) *
      cer0_synthesizer->length_effects
    )
  );

  cer0_synthesizer->effects[
    index_effect
  ] = (
    clic3_memory_allocate_raw(
      sizeof(
        struct cer0_effect
      )
    )
  );

  return (
    cer0_synthesizer->effects[
      index_effect
    ]
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

void cer0_synthesizer_frequency_play(
  struct cer0_synthesizer* synthesizer,
  float frequency
) {
  synthesizer->index_attack_sustain_decay_release = (
    0x00
  );

  cer0_synthesizer_frequency_set(
    synthesizer,
    frequency
  );
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

float cer0_synthesizer_poll_oscillators(
  struct cer0_synthesizer* synthesizer
) {
  float value_output = (
    0x00
  );

  for_oscillators {
    value_output = (
      value_output +
      cer0_oscillator_poll(
        &synthesizer->oscillators[
          index_oscillator
        ]
      ) /
      (float)
      synthesizer->length_oscillators
    );
  }
  
  return (
    value_output
  );
}

float cer0_synthesizer_poll_attack_sustain_decay_release(
  struct cer0_synthesizer* cer0_synthesizer
) {
  float amplitude_attack_sustain_decay_release;

  if (
    cer0_synthesizer->length_attack_sustain_decay_release ==
    0x00
  ) {
    amplitude_attack_sustain_decay_release = (
      0x01
    );
  } else if (
    cer0_synthesizer->length_attack_sustain_decay_release ==
    0x01
  ) {
    amplitude_attack_sustain_decay_release = (
      cer0_synthesizer->attack_sustain_decay_release_parameters.amplitude_release
    );
  } else {
    amplitude_attack_sustain_decay_release = (
      cer0_attack_sustain_decay_release_poll(
        &cer0_synthesizer->attack_sustain_decay_release_parameters,
        (
          (float)
          cer0_synthesizer->index_attack_sustain_decay_release /
          (float)
          (
            cer0_synthesizer->length_attack_sustain_decay_release -
            0x01
          )
        )
      )
    );

    cer0_synthesizer->index_attack_sustain_decay_release = (
      cer0_synthesizer->index_attack_sustain_decay_release +
      0x01
    );

    if (
      cer0_synthesizer->index_attack_sustain_decay_release >=
      cer0_synthesizer->length_attack_sustain_decay_release
    ) {
      cer0_synthesizer->index_attack_sustain_decay_release = (
        cer0_synthesizer->length_attack_sustain_decay_release -
        0x01
      );
    }
  }
  
  return (
    amplitude_attack_sustain_decay_release
  );
}

float cer0_synthesizer_poll_oscillators_attack_sustain_decay_release(
  struct cer0_synthesizer* cer0_synthesizer
) {
  return (
    cer0_synthesizer_poll_oscillators(
      cer0_synthesizer
    ) *
    cer0_synthesizer_poll_attack_sustain_decay_release(
      cer0_synthesizer
    )
  );
}

float cer0_synthesizer_effects_apply(
  struct cer0_synthesizer* cer0_synthesizer,
  float value
) {
  for (
    unsigned int index_effect = (
      0x00
    );
    (
      index_effect <
      cer0_synthesizer->length_effects
    );
    ++index_effect
  ) {
    value = (
      cer0_effect_poll(
        cer0_synthesizer->effects[
          index_effect
        ],
        0x00,
        value
      )
    );
  }

  return (
    value
  );
}

void cer0_synthesizer_effects_apply_stereo(
  struct cer0_synthesizer* cer0_synthesizer,
  float value[
    0x02
  ]
) {
  for (
    unsigned int index_effect = (
      0x00
    );
    (
      index_effect <
      cer0_synthesizer->length_effects
    );
    ++index_effect
  ) {
    value[
      0x00
    ] = (
      cer0_effect_poll(
        cer0_synthesizer->effects[
          index_effect
        ],
        0x00,
        value[
          0x00
        ]
      )
    );
    
    value[
      0x01
    ] = (
      cer0_effect_poll(
        cer0_synthesizer->effects[
          index_effect
        ],
        0x01,
        value[
          0x01
        ]
      )
    );
  }
}

float cer0_synthesizer_amplitude_apply(
  struct cer0_synthesizer* cer0_synthesizer,
  float value
) {
  return (
    cer0_synthesizer->amplitude *
    value
  );
}  

void cer0_synthesizer_amplitude_apply_stereo(
  struct cer0_synthesizer* cer0_synthesizer,
  float value[
    0x02
  ]
) {
  value[
    0x00
  ] = (
    cer0_synthesizer->amplitude *
    value[
      0x00
    ]
  );
  
  value[
    0x01
  ] = (
    cer0_synthesizer->amplitude *
    value[
      0x01
    ]
  );
} 

float cer0_synthesizer_poll(
  struct cer0_synthesizer* cer0_synthesizer
) {
  return (
    cer0_synthesizer_amplitude_apply(
      cer0_synthesizer,
      cer0_synthesizer_effects_apply(
        cer0_synthesizer,
        cer0_synthesizer_poll_oscillators_attack_sustain_decay_release(
          cer0_synthesizer
        )
      )
    )
  );
}

void cer0_synthesizer_poll_stereo(
  struct cer0_synthesizer* cer0_synthesizer,
  float result[
    0x02
  ]
) {
  cer0_pan_apply_stereo(
    cer0_synthesizer_poll_oscillators_attack_sustain_decay_release(
      cer0_synthesizer
    ),
    cer0_synthesizer->pan,
    result
  );
  
  cer0_synthesizer_amplitude_apply_stereo(
    cer0_synthesizer,
    result
  );
  
  cer0_synthesizer_effects_apply_stereo(
    cer0_synthesizer,
    result
  );
}

void cer0_synthesizer_destroy(
  struct cer0_synthesizer* synthesizer
) {
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
    cer0_effect_destroy(
      synthesizer->effects[
        index_effect
      ]
    );

    clic3_memory_free_raw(
      synthesizer->effects[
        index_effect
      ]
    );
  }

  clic3_memory_free_raw(
    synthesizer->effects
  );

  clic3_memory_free_raw(
    synthesizer->oscillators
  );
}
