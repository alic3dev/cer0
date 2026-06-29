#include <cer0_mix_mode.h>

float cer0_mix_mode_mix(
  float input_dry,
  float input_wet,
  float mix,
  enum cer0_mix_mode cer0_mix_mode
) {
  switch (
    cer0_mix_mode
  ) {
    case cer0_mix_mode_balance: {
      return (
        (
          input_dry *
          (
            0x01 -
            mix
          )
        ) +
        (
          input_wet *
          mix
        )
      );
    }
    case cer0_mix_mode_wet: {
      return (
        input_wet
      );
    }
    case cer0_mix_mode_dry: {
      return (
        input_dry
      );
    }
    default: {
      break;
    }
  }

  return (
    input_dry
  );
}
