#ifndef __CER0_AUDIO_OUTPUT
#define __CER0_AUDIO_OUTPUT

#include <CoreAudio/CoreAudio.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/hid/IOHIDKeys.h>
#include <IOKit/hid/IOHIDManager.h>
#include <IOKit/usb/USBSpec.h>

#include <sys/param.h>

#define CER0_AUDIO_OUTPUT_CHANNEL_LEFT = 0;
#define CER0_AUDIO_OUTPUT_CHANNEL_RIGHT = 1;

typedef OSStatus (*cer0_audio_output_io_proc)(
  AudioObjectID,
  const AudioTimeStamp*,
  const AudioBufferList *,
  const AudioTimeStamp *,
  AudioBufferList *,
  const AudioTimeStamp *,
  void *
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
  cer0_audio_output_io_proc
);

unsigned char cer0_audio_output_cleanup(
  struct cer0_audio_output*
);

#endif
