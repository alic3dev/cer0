#ifndef __cer0_signal_h
#define __cer0_signal_h

#include <cer0_constants.h>

#define cer0_length_signals 0x06
#define cer0_length_signals_extended 0x07

#define cer0_name_signal_sawtooth_down "sawtooth_down"
#define cer0_name_signal_sawtooth_up "sawtooth_up"
#define cer0_name_signal_sine "sine"
#define cer0_name_signal_square "square"
#define cer0_name_signal_triangle "triangle"
#define cer0_name_signal_white_noise "white_noise"
#define cer0_name_signal_sine_alice "sine_alice"

enum cer0_signal {
  sawtooth_down = 0x00,
  sawtooth_up   = 0x01,
  sine          = 0x02,
  square        = 0x03,
  triangle      = 0x04,
  white_noise   = 0x05,
  sine_alice    = 0x06
};

typedef float (*cer0_signal_function)(
  float
);

float cer0_signal_sine(
  float
);

float cer0_signal_sine_alice(
  float phase
);

float cer0_signal_white_noise(
  float
);

float cer0_signal_sawtooth_up(
  float
);

float cer0_signal_sawtooth_down(
  float
);

float cer0_signal_square(
  float
);

float cer0_signal_triangle(
  float
);

extern char* cer0_signal_name_lookup[
  cer0_length_signals_extended
];

extern cer0_signal_function cer0_signal_function_lookup[
  cer0_length_signals_extended
];

#endif
