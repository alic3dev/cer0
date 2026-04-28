#include <cer0_attack_sustain_decay_release.h>

void cer0_attack_sustain_decay_release_parameters_initialize(
  struct cer0_attack_sustain_decay_release_parameters* cer0_attack_sustain_decay_release_parameters
) {
  cer0_attack_sustain_decay_release_parameters->attack = (
    0x01
  );

  cer0_attack_sustain_decay_release_parameters->sustain = (
    0x01
  );

  cer0_attack_sustain_decay_release_parameters->decay = (
    0x01
  );

  cer0_attack_sustain_decay_release_parameters->release = (
    0x01
  );

  cer0_attack_sustain_decay_release_parameters->amplitude_initial = (
    0x00
  );

  cer0_attack_sustain_decay_release_parameters->amplitude_attack = (
    0x01
  );

  cer0_attack_sustain_decay_release_parameters->amplitude_sustain = (
    0.75f
  );

  cer0_attack_sustain_decay_release_parameters->amplitude_decay = (
    0.5f
  );

  cer0_attack_sustain_decay_release_parameters->poll_ramp_attack = (
    cer0_ramp_poll_sine_beginning_ending
  );

  cer0_attack_sustain_decay_release_parameters->poll_ramp_sustain = (
    cer0_ramp_poll_sine_beginning_ending
  );

  cer0_attack_sustain_decay_release_parameters->poll_ramp_decay = (
    cer0_ramp_poll_sine_beginning_ending
  );

  cer0_attack_sustain_decay_release_parameters->poll_ramp_release = (
    cer0_ramp_poll_sine_beginning_ending
  );
}

float cer0_attack_sustain_decay_release_poll(
  struct cer0_attack_sustain_decay_release_parameters* cer0_attack_sustain_decay_release_parameters,
  float percentage_lifespan
) {
  if (
    percentage_lifespan >=
    0x01
  ) {
    return (
      cer0_attack_sustain_decay_release_parameters->amplitude_release
    );
  }

  float total = (
    cer0_attack_sustain_decay_release_parameters->attack +
    cer0_attack_sustain_decay_release_parameters->sustain +
    cer0_attack_sustain_decay_release_parameters->decay +
    cer0_attack_sustain_decay_release_parameters->release
  );

  if (
    total <=
    0x00
  ) {
    return (
      cer0_attack_sustain_decay_release_parameters->amplitude_release
    );
  }

  float percentage_lifespan_conceptualized = (
    percentage_lifespan *
    total
  );

  float value_starting;
  float value_ending;
  
  cer0_ramp_function_poll poll_ramp;

  if (
    percentage_lifespan_conceptualized <
    cer0_attack_sustain_decay_release_parameters->attack
  ) {
    percentage_lifespan_conceptualized = (
      percentage_lifespan_conceptualized /
      cer0_attack_sustain_decay_release_parameters->attack
    );

    value_starting = (
      cer0_attack_sustain_decay_release_parameters->amplitude_initial
    );

    value_ending = (
      cer0_attack_sustain_decay_release_parameters->amplitude_attack
    );

    poll_ramp = (
      cer0_attack_sustain_decay_release_parameters->poll_ramp_attack
    );
  } else if (
    percentage_lifespan_conceptualized <
    (
      cer0_attack_sustain_decay_release_parameters->attack +
      cer0_attack_sustain_decay_release_parameters->sustain
    )
  ) {
    percentage_lifespan_conceptualized = (
      (
        percentage_lifespan_conceptualized -
        cer0_attack_sustain_decay_release_parameters->attack
      ) /
      cer0_attack_sustain_decay_release_parameters->sustain
    );

    value_starting = (
      cer0_attack_sustain_decay_release_parameters->amplitude_attack
    );

    value_ending = (
      cer0_attack_sustain_decay_release_parameters->amplitude_sustain
    );

    poll_ramp = (
      cer0_attack_sustain_decay_release_parameters->poll_ramp_sustain
    );
  } else if (
    percentage_lifespan_conceptualized <
    (
      cer0_attack_sustain_decay_release_parameters->attack +
      cer0_attack_sustain_decay_release_parameters->sustain +
      cer0_attack_sustain_decay_release_parameters->decay
    )
  ) {
    percentage_lifespan_conceptualized = (
      (
        percentage_lifespan_conceptualized -
        cer0_attack_sustain_decay_release_parameters->attack -
        cer0_attack_sustain_decay_release_parameters->sustain
      ) /
      cer0_attack_sustain_decay_release_parameters->decay
    );

    value_starting = (
      cer0_attack_sustain_decay_release_parameters->amplitude_sustain
    );

    value_ending = (
      cer0_attack_sustain_decay_release_parameters->amplitude_decay
    );

    poll_ramp = (
      cer0_attack_sustain_decay_release_parameters->poll_ramp_decay
    );
  } else {
    percentage_lifespan_conceptualized = (
      (
        percentage_lifespan_conceptualized -
        cer0_attack_sustain_decay_release_parameters->attack -
        cer0_attack_sustain_decay_release_parameters->sustain -
        cer0_attack_sustain_decay_release_parameters->decay
      ) /
      cer0_attack_sustain_decay_release_parameters->release
    );

    value_starting = (
      cer0_attack_sustain_decay_release_parameters->amplitude_decay
    );

    value_ending = (
      cer0_attack_sustain_decay_release_parameters->amplitude_release
    );

    poll_ramp = (
      cer0_attack_sustain_decay_release_parameters->poll_ramp_release
    );
  }

  return (
    value_starting +
    poll_ramp(
      (
        value_ending -
        value_starting
      ),
      percentage_lifespan_conceptualized
    )
  );  
}
