#include <cer0_effects/cer0_effect_delay.h>

#include <cer0_effect.h>

#include <clic3_memory.h>

void cer0_effect_delay_initialize(
  struct cer0_effect* cer0_effect_delay,
  unsigned char length_channels
) {
  cer0_effect_initialize(
    cer0_effect_delay
  );

  cer0_effect_delay->data = (
    clic3_memory_allocate_raw(
      sizeof(
        struct cer0_effect_delay_data
      )
    )
  );

  struct cer0_effect_delay_data* cer0_effect_delay_data = (
    cer0_effect_delay->data
  );

  cer0_effect_delay_data->length_channels = (
    length_channels
  );

  cer0_effect_delay_data->length_frames_buffer = (
    0x01ffff
  );

  cer0_effect_delay_data->index_frames_buffer = (
    clic3_memory_allocate_raw(
      sizeof(
        unsigned int
      ) *
      cer0_effect_delay_data->length_channels
    )
  );

  cer0_effect_delay_data->frames_buffer = (
    clic3_memory_allocate_raw(
      sizeof(
        void*
      ) *
      cer0_effect_delay_data->length_channels
    )
  );

  for (
    unsigned char index_channel = (
      0x00
    );
    (
      index_channel <
      cer0_effect_delay_data->length_channels
    );
    ++index_channel
  ) {
    cer0_effect_delay_data->frames_buffer[
      index_channel
    ] = (
      clic3_memory_allocate_raw(
        sizeof(
          float
        ) *
        cer0_effect_delay_data->length_frames_buffer
      )
    );

    for (
      unsigned int index_frame = (
        0x00
      );
      (
        index_frame <
        cer0_effect_delay_data->length_frames_buffer
      );
      ++index_frame
    ) {
      cer0_effect_delay_data->frames_buffer[
        index_channel
      ][
        index_frame
      ] = (
        0x00
      );
    }

    cer0_effect_delay_data->index_frames_buffer[
      index_channel
    ] = (
      0x00
    );
  }

  cer0_effect_delay_data->decay = (
    0.5f
  );

  cer0_effect_delay->poll = (
    cer0_effect_delay_poll
  );

  cer0_effect_delay->destroy = (
    cer0_effect_delay->destroy
  );
}

void cer0_effect_delay_length_frames_buffer_set(
  struct cer0_effect* cer0_effect_delay,
  unsigned int length_frames
) {
  struct cer0_effect_delay_data* cer0_effect_delay_data = (
    cer0_effect_delay->data
  );

  unsigned int length_frames_buffer_previous = (
    cer0_effect_delay_data->length_frames_buffer
  );

  cer0_effect_delay_data->length_frames_buffer = (
    length_frames
  );

  clic3_memory_reallocate_raw(
    &cer0_effect_delay_data->frames_buffer,
    (
      sizeof(
        void*
      ) *
      cer0_effect_delay_data->length_channels
    )
  );

  clic3_memory_reallocate_raw(
    &cer0_effect_delay_data->index_frames_buffer,
    (
      sizeof(
        unsigned int*
      ) *
      cer0_effect_delay_data->length_channels
    )
  );

  for (
    unsigned char index_channel = (
      0x00
    );
    (
      index_channel <
      cer0_effect_delay_data->length_channels
    );
    ++index_channel
  ) {
    clic3_memory_reallocate_raw(
      &cer0_effect_delay_data->frames_buffer[
        index_channel
      ],
      (
        sizeof(
          float
        ) *
        cer0_effect_delay_data->length_frames_buffer
      )
    );

    for (
      unsigned int index_frame = (
        length_frames_buffer_previous
      );
      (
        index_frame <
        cer0_effect_delay_data->length_frames_buffer
      );
      ++index_frame
    ) {
      cer0_effect_delay_data->frames_buffer[
        index_frame
      ] = (
        0x00
      );
    }

    cer0_effect_delay_data->index_frames_buffer[
      index_channel
    ] = (
      cer0_effect_delay_data->index_frames_buffer[
        index_channel
      ] %
      cer0_effect_delay_data->length_frames_buffer
    );
  }
}

float cer0_effect_delay_poll(
  struct cer0_effect* cer0_effect_delay,
  unsigned char channel,
  float value_input
) {
  struct cer0_effect_delay_data* cer0_effect_delay_data = (
    cer0_effect_delay->data
  );

  if (
    channel >
    (
      cer0_effect_delay_data->length_channels -
      0x01
    )
  ) {
    return (
      value_input
    );
  }

  cer0_effect_delay_data->frames_buffer[
    channel
  ][
    cer0_effect_delay_data->index_frames_buffer[
      channel
    ]
  ] = (
    cer0_effect_delay_data->frames_buffer[
      channel
    ][
      cer0_effect_delay_data->index_frames_buffer[
        channel
      ]
    ] *
    cer0_effect_delay_data->decay +
    value_input
  );

  cer0_effect_delay_data->index_frames_buffer[
    channel
  ] = (
    (
      cer0_effect_delay_data->index_frames_buffer[
        channel
      ] +
      0x01
    ) %
    cer0_effect_delay_data->length_frames_buffer
  );

  return (
    cer0_effect_delay_data->frames_buffer[
      channel
    ][
      cer0_effect_delay_data->index_frames_buffer[
        channel
      ]
    ]
  );
}

void cer0_effect_delay_destroy(
  struct cer0_effect* cer0_effect_delay
) {
  struct cer0_effect_delay_data* cer0_effect_delay_data = (
    cer0_effect_delay->data
  );

  for (
    unsigned char index_channel = (
      0x00
    );
    (
      index_channel <
      cer0_effect_delay_data->length_channels
    );
    ++index_channel
  ) {
    clic3_memory_free_raw(
      cer0_effect_delay_data->frames_buffer[
        index_channel
      ]
    );
  }

  clic3_memory_free_raw(
    cer0_effect_delay_data->frames_buffer
  );

  clic3_memory_free_raw(
    cer0_effect_delay_data->index_frames_buffer
  );

  clic3_memory_free_raw(
    cer0_effect_delay->data
  );
}
