#include <cer0_effects/cer0_effect_bit_crush.h>

#include <cer0_effect.h>

#include <clic3_memory.h>

#include <math_c_absolute.h>

void cer0_effect_bit_crush_initialize(
  struct cer0_effect* cer0_effect_bit_crush,
  unsigned char bits
) {
  cer0_effect_initialize(
    cer0_effect_bit_crush
  );

  cer0_effect_bit_crush->data = (
    clic3_memory_allocate_raw(
      sizeof(
        struct cer0_effect_bit_crush_data
      )
    )
  );

  struct cer0_effect_bit_crush_data* cer0_effect_bit_crush_data = (
    cer0_effect_bit_crush->data
  );

  cer0_effect_bit_crush_data->mode = (
    cer0_effect_bit_crush_mode_bits
  );

  cer0_effect_bit_crush_data->range = (
    0x01
  );

  cer0_effect_bit_crush_bits_set(
    cer0_effect_bit_crush,
    bits
  );

  cer0_effect_bit_crush->poll = (
    cer0_effect_bit_crush_poll
  );
}

void cer0_effect_bit_crush_mode_set(
  struct cer0_effect* cer0_effect_bit_crush,
  unsigned char cer0_effect_bit_crush_mode
) {
  struct cer0_effect_bit_crush_data* cer0_effect_bit_crush_data = (
    cer0_effect_bit_crush->data
  );

  cer0_effect_bit_crush_data->mode = (
    cer0_effect_bit_crush_mode
  );

  cer0_effect_bit_crush_bits_set(
    cer0_effect_bit_crush,
    cer0_effect_bit_crush_data->bits
  );
}

void cer0_effect_bit_crush_bits_set(
  struct cer0_effect* cer0_effect_bit_crush,
  unsigned char bits
) {
  struct cer0_effect_bit_crush_data* cer0_effect_bit_crush_data = (
    cer0_effect_bit_crush->data
  );

  cer0_effect_bit_crush_data->bits = (
    bits
  );

  cer0_effect_bit_crush_data->value_maximum = (
    0x00
  );

  for (
    unsigned char index_bit = (
      0x00
    );
    (
      index_bit <
      cer0_effect_bit_crush_data->bits
    );
    ++index_bit
  ) {
    switch (
      cer0_effect_bit_crush_data->mode
    ) {
      case cer0_effect_bit_crush_mode_bits: {
        cer0_effect_bit_crush_data->value_maximum = (
          (
            cer0_effect_bit_crush_data->value_maximum <<
            0b00000001
          ) +
          0b00000001
        );

        break;
      }
      case cer0_effect_bit_crush_mode_value: {
        cer0_effect_bit_crush_data->value_maximum = (
          cer0_effect_bit_crush_data->value_maximum +
          0b00000001
        );

        break;
      }
    }
  }
}

float cer0_effect_bit_crush_poll(
  struct cer0_effect* cer0_effect_bit_crush,
  unsigned char channel,
  float input_value
) {
  struct cer0_effect_bit_crush_data* cer0_effect_bit_crush_data = (
    cer0_effect_bit_crush->data
  );

  float wet_value = (
    (float)
    (
      (unsigned int)
      (
        (
          input_value +
          cer0_effect_bit_crush_data->range
        ) /
        (
          cer0_effect_bit_crush_data->range *
          0x02
        ) *
        cer0_effect_bit_crush_data->value_maximum
      )
    ) /
    (float)
    cer0_effect_bit_crush_data->value_maximum
  );

  wet_value = (
    wet_value *
    (
      cer0_effect_bit_crush_data->range *
      0x02
    ) -
    cer0_effect_bit_crush_data->range
  );

  return (
    wet_value
  );
}
