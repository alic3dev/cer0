#include <cer0_synthesizer_speech.h>

#include <cer0_synthesizer.h>

#include <clic3_bytes.h>
#include <clic3_memory.h>

void cer0_synthesier_speech_initialize(
  struct cer0_synthesizer_speech* cer0_synthesizer_speech,
  float rate_sample
) {
  cer0_synthesizer_initialize(
    &cer0_synthesizer_speech->synthesizer,
    rate_sample
  );
  
  cer0_synthesizer_speech->segments = (
    clic3_memory_allocate_raw(
      0x00
    )
  );
  
  cer0_synthesizer_speech->length_segments = (
    0x00
  );
}

void cer0_synthesizer_speech_speak_segments(
  struct cer0_synthesizer_speech* cer0_synthesizer_speech,
  struct cer0_synthesizer_speech_segment* segments,
  unsigned int length_segments
) {
  cer0_synthesizer_speech->length_segments = (
    cer0_synthesizer_speech->length_segments +
    length_segments
  );
  
  clic3_memory_reallocate_raw(
    &cer0_synthesizer_speech->segments,
    (
      sizeof(
        struct cer0_synthesizer_speech_segment
      ) *
      cer0_synthesizer_speech->length_segments
    )
  );
  
  for (
    unsigned int index_segment = (
      0x00
    );
    (
      index_segment <
      length_segments
    );
    ++index_segment
  ) {
    clic3_bytes_copy(
      (
        cer0_synthesizer_speech->segments +
        sizeof(
          struct cer0_synthesizer_speech_segment
        ) *
        (
          cer0_synthesizer_speech->length_segments -
          length_segments +
          index_segment
        )
      ),
      (
        segments +
        sizeof(
          struct cer0_synthesizer_speech_segment
        ) *
        index_segment
      ),
      sizeof(
        struct cer0_synthesizer_speech_segment
      )
    );
  }
}

void cer0_synthesizer_speech_segment_next(
  struct cer0_synthesizer_speech* cer0_synthesizer_speech
) {
  if (
    cer0_synthesizer_speech->length_segments ==
    0x00
  ) {
    return;
  }

  cer0_synthesizer_speech->length_segments = (
    cer0_synthesizer_speech->length_segments -
    0x01
  );
  
  for (
    unsigned int index_segment = (
      0x00
    );
    (
      index_segment <
      cer0_synthesizer_speech->length_segments
    );
    ++index_segment
  ) {
    clic3_bytes_copy(
      (
        cer0_synthesizer_speech->segments +
        sizeof(
          struct cer0_synthesizer_speech_segment
        ) *
        index_segment
      ),
      (
        cer0_synthesizer_speech->segments +
        sizeof(
          struct cer0_synthesizer_speech_segment
        ) *
        (
          index_segment +
          0x01
        )
      ),
      sizeof(
        struct cer0_synthesizer_speech_segment
      )
    );
  }
  
  clic3_memory_reallocate_raw(
    &cer0_synthesizer_speech->segments,
    (
      sizeof(
        struct cer0_synthesizer_speech_segment
      ) *
      cer0_synthesizer_speech->length_segments
    )
  );
}

float cer0_synthesizer_speech_poll(
  struct cer0_synthesizer_speech* cer0_synthesizer_speech
) {
  return (
    0x00
  );
}

void cer0_synthesizer_speech_destroy(
  struct cer0_synthesizer_speech* cer0_synthesizer_speech
) {
  cer0_synthesizer_destroy(
    &cer0_synthesizer_speech->synthesizer
  );
  
  clic3_memory_free_raw(
    cer0_synthesizer_speech->segments
  );
}
