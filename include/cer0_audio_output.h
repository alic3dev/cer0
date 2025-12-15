#ifndef __cer0_audio_output
#define __cer0_audio_output

#if target_ios
#include <AVFAudio/AVFAudio.h>
#else
#include <CoreAudio/CoreAudio.h>
#endif

#define cer0_audio_output_channel_left = 0;
#define cer0_audio_output_channel_right = 1;

#if target_ios
typedef OSStatus (*cer0_audio_output_io_proc)(
  unsigned char,
  const AudioTimeStamp* _Nonnull,
  AVAudioFrameCount,
  AudioBufferList* _Nonnull,
  void* _Nullable
);
#else
typedef OSStatus (*cer0_audio_output_io_proc)(
  AudioObjectID,
  const AudioTimeStamp*,
  const AudioBufferList*,
  const AudioTimeStamp*,
  AudioBufferList*,
  const AudioTimeStamp*,
  void*
);
#endif

struct cer0_audio_output {
  #if target_ios
  AVAudioEngine* _Nonnull engine_audio;
  AVAudioSourceNodeRenderBlock _Nonnull render_block;
  #else
  AudioObjectPropertyAddress* audio_object_property_address;
  
  AudioDeviceID device;
  unsigned int device_size;

  AudioDeviceIOProcID io_proc_id;
  #endif

  cer0_audio_output_io_proc io_proc;

  float sample_rate;
};

unsigned char cer0_audio_output_initialize(
  struct cer0_audio_output*,
  cer0_audio_output_io_proc,
  void*
);

unsigned char cer0_audio_output_destroy(
  struct cer0_audio_output*
);

#endif
