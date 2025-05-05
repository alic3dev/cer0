#ifndef signals_h
#define signals_h

#include "constants.h"

#define CER0_SIGNALS_LENGTH 6

typedef float (*cer0_signal_function)(float);

float cer0_signal_sine(float);
float cer0_signal_white_noise(float);
float cer0_signal_sawtooth_up(float);
float cer0_signal_sawtooth_down(float);
float cer0_signal_square(float);
float cer0_signal_triangle(float);

extern char *cer0_signal_name_lookup[CER0_SIGNALS_LENGTH];
extern cer0_signal_function cer0_signal_function_lookup[CER0_SIGNALS_LENGTH];

#endif
