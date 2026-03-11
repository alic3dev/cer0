#if !target_os_ios

#include <cer0_audio_output.h>

#include <cer0_parameters.h>

#include <CoreAudio/CoreAudio.h>

#include <sys/param.h>

unsigned char cer0_audio_output_initialize(
  struct cer0_audio_output* cer0_audio_output,
  cer0_audio_output_io_proc io_proc,
  void* data_io_proc
) {
  AudioObjectPropertyAddress audio_object_property_address = {
    .mSelector = (
      kAudioHardwarePropertyDefaultOutputDevice
    ),
    .mScope = (
      kAudioObjectPropertyScopeOutput
    ),
    .mElement = (
      kAudioObjectPropertyElementMain
    )
  };

  cer0_audio_output->device = (
    kAudioDeviceUnknown
  );

  cer0_audio_output->device_size = (
    sizeof(
      cer0_audio_output->device
    )
  );

  cer0_audio_output->io_proc = (
    io_proc
  );

  cer0_audio_output->data_io_proc = (
    data_io_proc
  );

  AudioObjectGetPropertyData(
    kAudioObjectSystemObject,
    &audio_object_property_address,
    0,
    0,
    &cer0_audio_output->device_size,
    &cer0_audio_output->device
  );

  AudioObjectPropertyAddress address_property_changed_device = {
    .mSelector = (
      kAudioHardwarePropertyDefaultOutputDevice
    ),
    .mScope = (
      kAudioObjectPropertyScopeGlobal
    ),
    .mElement = (
      kAudioObjectPropertyElementMain
    )
  };

  AudioObjectAddPropertyListener(
    kAudioObjectSystemObject,
    &address_property_changed_device,
    cer0_audio_output_changed_device,
    cer0_audio_output
  );

  AudioObjectPropertyAddress address_property_object_audio_rate_sample  = {
    .mSelector = kAudioDevicePropertyActualSampleRate,
    .mScope = kAudioObjectPropertyScopeOutput,
    .mElement = kAudioObjectPropertyElementMain
  };

  unsigned char has_rate_sample = (
    AudioObjectHasProperty(
      cer0_audio_output->device,
      &address_property_object_audio_rate_sample
    )
  );

  if (
    has_rate_sample != 0
  ) {
    double rate_sample_device;

    unsigned int length_double = (
      sizeof(
        double
      )
    );

    AudioObjectGetPropertyData(
      cer0_audio_output->device,
      &address_property_object_audio_rate_sample,
      0,
      0,
      &length_double,
      &rate_sample_device
    );

    cer0_audio_output->sample_rate = (
      rate_sample_device
    );
  } else {
    cer0_audio_output->sample_rate = (
      44100.0f
    );
  }

  int status_device_start = AudioDeviceStart(
    cer0_audio_output->device,
    0
  );

  if (status_device_start != 0) {
    if (cer0_parameter_log_level != cer0_parameter_log_level_none) {
      fprintf(
        stderr,
        "failed_to_start:device->{%i:%i}\n",
        cer0_audio_output->device,
        status_device_start
      );
    }

    return 1;
  }

  int status_create_io_proc_id = AudioDeviceCreateIOProcID(
    cer0_audio_output->device,
    cer0_audio_output->io_proc,
    data_io_proc,
    &cer0_audio_output->io_proc_id
  );

  if (
    status_create_io_proc_id != 0
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failed_to_create:io_proc_id:%i\n",
        status_create_io_proc_id
      );
    }

    return 1;
  }

  int status_audio_device_start = AudioDeviceStart(
    cer0_audio_output->device,
    cer0_audio_output->io_proc_id
  );

  if (
    status_audio_device_start != 0
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failed_to_start:[device|io_proc_id]->{[%i|%i]}\n",
        cer0_audio_output->device,
        status_audio_device_start
      );
    }

    return 1;
  }

  return (
    cer0_audio_output->io_proc_id == 0
    ? 1
    : 0
  );
}

int cer0_audio_output_changed_device(
  unsigned int id_object_audio,
  unsigned int length_addressess_property_object_audio,
  const AudioObjectPropertyAddress* address_property_object_audio,
  void* data_cer0_audio_output
) {
  struct cer0_audio_output* cer0_audio_output = (
    data_cer0_audio_output
  );

  cer0_audio_output_destroy(
    cer0_audio_output
  );

  cer0_audio_output_initialize(
    cer0_audio_output,
    cer0_audio_output->io_proc,
    cer0_audio_output->data_io_proc
  );

  return (
    0x00
  );
}

unsigned char cer0_audio_output_destroy(
  struct cer0_audio_output* cer0_audio_output
) {
  unsigned char result = (
    0x00
  );

  int status_audio_device_destroy_io_proc_id = (
    AudioDeviceDestroyIOProcID(
      cer0_audio_output->device,
      cer0_audio_output->io_proc_id
    )
  );

  if (
    status_audio_device_destroy_io_proc_id !=
    0x00
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failure_destroying_input_output_process->{%i}\n",
        status_audio_device_destroy_io_proc_id
      );
    }

    result = (
      result +
      0x01
    );
  }

  int status_audio_device_stop = (
    AudioDeviceStop(
      cer0_audio_output->device,
      cer0_audio_output->io_proc_id
    )
  );

  if (
    status_audio_device_stop !=
    0x00
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failure_stopping_device->{%i:%i}\n",
        cer0_audio_output->device,
        status_audio_device_stop
      );
    }

    result = (
      result +
      0x01
    );
  }

  status_audio_device_stop = AudioDeviceStop(
    cer0_audio_output->device,
    0
  );

  if (
    status_audio_device_stop !=
    0x00
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failure_stopping_device->{%i:%i};\n",
        cer0_audio_output->device,
        status_audio_device_stop
      );
    }

    result = (
      result +
      0x01
    );
  }

  int status_unload = (
    AudioHardwareUnload()
  );

  if (
    status_unload !=
    0x00
  ) {
    result = (
      result +
      0x01
    );
  }

  return (
    result
  );
}

#endif
