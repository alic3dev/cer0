#include <cer0_audio_output.h>

#if !cer0_audio_disabled
#include <cer0_parameters.h>

#include <CoreAudio/CoreAudio.h>

#include <sys/param.h>

unsigned char cer0_audio_output_initialize(
  struct cer0_audio_output* audio_output,
  cer0_audio_output_io_proc io_proc,
  void* data_io_proc
) {
  static AudioObjectPropertyAddress audio_object_property_address = {
    kAudioHardwarePropertyDefaultSystemOutputDevice,
    kAudioObjectPropertyScopeOutput,
    kAudioObjectPropertyElementMain
  };

  audio_output->audio_object_property_address = &audio_object_property_address;

  audio_output->device = kAudioDeviceUnknown;
  audio_output->device_size = sizeof(audio_output->device);

  audio_output->io_proc = io_proc;

  AudioObjectGetPropertyData(
    kAudioObjectSystemObject,
    audio_output->audio_object_property_address,
    0,
    (void*)0,
    &audio_output->device_size,
    &audio_output->device
  );

  audio_output->sample_rate = 44100.0f;

  OSStatus status_device_start = AudioDeviceStart(
    audio_output->device,
    (void*)0
  );

  if (status_device_start != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "failed_to_start:device->{%i:%i}\n",
        audio_output->device,
        status_device_start
      );
    }

    return 1;
  }

  OSStatus status_create_io_proc_id = AudioDeviceCreateIOProcID(
    audio_output->device,
    audio_output->io_proc,
    data_io_proc,
    &audio_output->io_proc_id
  );

  if (status_create_io_proc_id != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "failed_to_create:io_proc_id:%i\n",
        status_create_io_proc_id
      );
    }

    return 1;
  }

  OSStatus status_audio_device_start = AudioDeviceStart(
    audio_output->device,
    audio_output->io_proc_id
  );

  if (status_audio_device_start != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "failed_to_start:[device|io_proc_id]->{[%i|%i]}\n",
        audio_output->device,
        status_audio_device_start
      );
    }

    return 1;
  }

  return audio_output->io_proc_id == (void*)0 ? 1 : 0;
}

unsigned char cer0_audio_output_destroy(
  struct cer0_audio_output* audio_output
) {
  unsigned char result = 0;

  OSStatus status_audio_device_destroy_io_proc_id = AudioDeviceDestroyIOProcID(
    audio_output->device,
    audio_output->io_proc_id
  );

  if (status_audio_device_destroy_io_proc_id != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "failed_to_destroy:io_proc_id->{%i}\n",
        status_audio_device_destroy_io_proc_id
      );
    }

    result = (
      result + 1
    );
  }

  OSStatus status_audio_device_stop = AudioDeviceStop(
    audio_output->device,
    audio_output->io_proc_id
  );

  if (status_audio_device_stop != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "failed_to_stop_:[device|io_proc_id]->{[%i|%i]}\n",
        audio_output->device,
        status_audio_device_stop
      );
    }

    result = (
      result + 1
    );
  }

  status_audio_device_stop = AudioDeviceStop(
    audio_output->device,
    (void*)0
  );

  if (status_audio_device_stop != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "Failed to stop device [%i]: %i\n",
        audio_output->device,
        status_audio_device_stop
      );
    }

    result = (
      result + 1
    );
  }

  return result;
}

#endif
