#include <cer0_signal.h>
#include <cer0_constants.h>

#include <math.h>
#include <stdint.h>
#include <stdlib.h>

float cer0_signal_sine(
  float phase
) {
  return sin(phase);
}

float cer0_signal_white_noise(
  float phase
) {
  return ((
    (float)(arc4random_uniform(__UINT32_MAX__)) / 
    (float)(UINT32_MAX)
  ) * 2.0f - 1.0f);
}

float cer0_signal_sawtooth_up(
  float phase
) {
  return 1.0f - 2.0f * (phase * (1.0f / cer0_two_pi));
}

float cer0_signal_sawtooth_down(
  float phase
) {
  return (2.0f * (phase * (1.0f / cer0_two_pi))) - 1.0f;
}

float cer0_signal_square(
  float phase
) {
  if (phase <= M_PI) {
    return 1.0f;
  } else {
    return -1.0f;
  }
}

float cer0_signal_triangle(
  float phase
) {
  float value = (2.0f * (phase * (1.0f / cer0_two_pi))) - 1.0f;

  if (value < 0.0f) {
    value = -value;
  }

  return 2.0f * (value - 0.5f);
}

char *cer0_signal_name_lookup[cer0_length_signals] = {
  cer0_name_signal_sawtooth_down,
  cer0_name_signal_sawtooth_up,
  cer0_name_signal_sine,
  cer0_name_signal_square,
  cer0_name_signal_triangle,
  cer0_name_signal_white_noise
};

cer0_signal_function cer0_signal_function_lookup[cer0_length_signals] = {
  cer0_signal_sawtooth_down,
  cer0_signal_sawtooth_up,
  cer0_signal_sine,
  cer0_signal_square,
  cer0_signal_triangle,
  cer0_signal_white_noise
};
