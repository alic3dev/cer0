#ifndef __cer0_signals_h
#define __cer0_signals_h

#include <cer0_constants.h>

#define cer0_length_signals 6

#define cer0_name_signal_sawtooth_down "Sawtooth Down"
#define cer0_name_signal_sawtooth_up "Sawtooth Up"
#define cer0_name_signal_sine "Sine"
#define cer0_name_signal_square "Square"
#define cer0_name_signal_triangle "Triangle"
#define cer0_name_signal_white_noise "White Noise"

typedef float (*cer0_signal_function)(float);

float cer0_signal_sine(float);
float cer0_signal_white_noise(float);
float cer0_signal_sawtooth_up(float);
float cer0_signal_sawtooth_down(float);
float cer0_signal_square(float);
float cer0_signal_triangle(float);

extern char *cer0_signal_name_lookup[cer0_length_signals];
extern cer0_signal_function cer0_signal_function_lookup[cer0_length_signals];

#endif
