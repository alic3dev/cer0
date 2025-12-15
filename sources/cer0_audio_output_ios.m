#if target_ios

#include <cer0_audio_output.h>

#include <cer0_parameters.h>

#include <AVFAudio/AVFAudio.h>

#include <sys/param.h>

unsigned char cer0_audio_output_initialize(
  struct cer0_audio_output* audio_output,
  cer0_audio_output_io_proc io_proc,
  void* data_io_proc
) {
  AVAudioSession* session_audio_shared = [
    AVAudioSession
    sharedInstance
  ];

  NSError* error = (
    (void*) 0
  );
  
  [session_audio_shared 
    setCategory: AVAudioSessionCategoryPlayback
    mode:AVAudioSessionModeDefault
    options:AVAudioSessionCategoryOptionMixWithOthers
    error: &error
  ];

  if (
    error != (void*) 0
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failed_to_start:audio_session\n"
      );
    }

    return 1;
  }
  
  [session_audio_shared
    setActive: 1
    error: &error
  ];

  if (
    error != (void*) 0
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failed_to_set_active:audio_session\n"
      );
    }

    return 1;
  }
  
  audio_output->engine_audio = [
    [
      AVAudioEngine
      alloc
    ]
    init
  ];
  
  AVAudioMixerNode* node_output = (
    audio_output->engine_audio.mainMixerNode
  );

  AVAudioFormat* format_output = [
    node_output
    inputFormatForBus: 0
  ];

  audio_output->io_proc = io_proc;

  audio_output->sample_rate = (
    format_output.sampleRate
  );

  AVAudioSourceNode* node_source = [
    [
      AVAudioSourceNode
      alloc
    ]
    initWithFormat: format_output
    renderBlock: ^int(
      bool* _Nonnull silence,
      const AudioTimeStamp* _Nonnull timestamp,
      AVAudioFrameCount frame_count,
      AudioBufferList* _Nonnull output_data
    ) {
      return audio_output->io_proc(
        *silence,
        timestamp,
        frame_count,
        output_data,
        data_io_proc
      );
    }
  ];

  [
    audio_output->engine_audio
    attachNode: node_source
  ];

  [
    audio_output->engine_audio
    connect: node_source
    to: node_output
    format: format_output
  ];

  [
    audio_output->engine_audio
    startAndReturnError: &error
  ];

  if (
    error != (void*) 0
  ) {
    if (
      cer0_parameter_log_level != cer0_parameter_log_level_none
    ) {
      fprintf(
        stderr,
        "failed_to_start:audio_engine\n"
      );
    }

    return 1;
  }

  return 0;
}

unsigned char cer0_audio_output_destroy(
  struct cer0_audio_output* audio_output
) {
  [
    audio_output->engine_audio stop
  ];

  return 0;
}

#endif
