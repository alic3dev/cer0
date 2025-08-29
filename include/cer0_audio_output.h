#ifndef __cer0_audio_output
#define __cer0_audio_output

#include <CoreAudio/CoreAudio.h>

#define cer0_audio_output_channel_left = 0;
#define cer0_audio_output_channel_right = 1;

typedef OSStatus (*cer0_audio_output_io_proc)(
  AudioObjectID,
  const AudioTimeStamp*,
  const AudioBufferList*,
  const AudioTimeStamp*,
  AudioBufferList*,
  const AudioTimeStamp*,
  void*
);

struct cer0_audio_output {
  AudioObjectPropertyAddress* audio_object_property_address;
  AudioDeviceID device;
  unsigned int device_size;
  cer0_audio_output_io_proc io_proc;
  AudioDeviceIOProcID io_proc_id;
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
