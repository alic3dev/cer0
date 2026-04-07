#ifndef __cer0_cer0_mix_mode_h
#define __cer0_cer0_mix_mode_h

enum cer0_mix_mode {
  cer0_mix_mode_balance = 0x00
};

float cer0_mix_mode_mix(
  float,
  float,
  float,
  enum cer0_mix_mode
);

#endif

