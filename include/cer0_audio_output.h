#ifndef __cer0_audio_output_h
#define __cer0_audio_output_h

#define cer0_audio_output_channel_left = 0;
#define cer0_audio_output_channel_right = 1;

#if target_ios
#include <cer0_audio_output_ios.h>
#else
#include <cer0_audio_output_macos.h>
#endif

#endif
