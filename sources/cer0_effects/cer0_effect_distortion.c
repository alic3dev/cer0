#include <cer0_effects/cer0_effect_distortion.h>

#include <cer0_effect.h>

#include <clic3_memory.h>

void cer0_effect_distortion_initialize(
  struct cer0_effect* cer0_effect_distortion
) {
  cer0_effect_initialize(
    cer0_effect_distortion
  );

  cer0_effect_distortion->data = (
    clic3_memory_allocate_raw(
      sizeof(
        struct cer0_effect_distortion_data
      )
    )
  );

  struct cer0_effect_distortion_data* cer0_effect_distortion_data = (
    cer0_effect_distortion->data
  );

  cer0_effect_distortion_data->gain = (
    2.0f
  );

  cer0_effect_distortion_data->noise = (
    0.3f
  );

  cer0_effect_distortion->poll = (
    cer0_effect_distortion_poll
  );
}

float cer0_effect_distortion_poll(
  struct cer0_effect* cer0_effect_distortion,
  unsigned char channel,
  float input_value
) {
  struct cer0_effect_distortion_data* cer0_effect_distortion_data = (
    cer0_effect_distortion->data
  );

  float wet_value = (
    input_value
  );

  unsigned char* input_value_bytes = (
    (unsigned char*)
    &wet_value
  );

  for (
    unsigned char index_byte = (
      0x00
    );
    (
      index_byte <
      sizeof(
        float
      )
    );
    ++index_byte
  ) {
    input_value_bytes[
      index_byte
    ] = (
      input_value_bytes[
        index_byte
      ] +
      input_value_bytes[
        index_byte
      ] *
      cer0_effect_distortion_data->noise
    );
  }

  if (
    wet_value >
    1.0f
  ) {
    wet_value = (
      wet_value -
      (unsigned int)
      wet_value
    );
  } else if (
    wet_value <
    -1.0f
  ) {
    wet_value = (
      wet_value -
      (signed int)
      wet_value
    );
  }

  return (
    wet_value
  );
}
