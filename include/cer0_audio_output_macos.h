#ifndef __cer0_audio_output_macos_h
#define __cer0_audio_output_macos_h

#if !target_os_ios

#include <CoreAudio/CoreAudio.h>

typedef int (*cer0_audio_output_io_proc)(
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

  AudioDeviceIOProcID io_proc_id;

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

#endif
