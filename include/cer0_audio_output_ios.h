#ifndef __cer0_audio_output
#define __cer0_audio_output

#if target_os_ios
#include <AVFAudio/AVFAudio.h>

typedef int (*cer0_audio_output_io_proc)(
  unsigned char,
  const AudioTimeStamp* _Nonnull,
  AVAudioFrameCount,
  AudioBufferList* _Nonnull,
  void* _Nullable
);

struct cer0_audio_output {
  AVAudioEngine* _Nonnull engine_audio;
  AVAudioSourceNodeRenderBlock _Nonnull render_block;

  cer0_audio_output_io_proc _Nonnull io_proc;

  float sample_rate;
};

unsigned char cer0_audio_output_initialize(
  struct cer0_audio_output* _Nonnull,
  cer0_audio_output_io_proc _Nonnull,
  void* _Nullable
);

unsigned char cer0_audio_output_destroy(
  struct cer0_audio_output* _Nonnull
);

#endif

#endif
