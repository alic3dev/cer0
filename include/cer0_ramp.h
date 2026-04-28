#ifndef __cer0_cer0_ramp_h
#define __cer0_cer0_ramp_h

typedef float (*cer0_ramp_function_poll)(
  float,
  float
);

enum cer0_ramp_type {
  cer0_ramp_type_linear                = 0x00,
  cer0_ramp_type_sine                  = 0x01,
  cer0_ramp_type_sine_beginning_ending = 0x02,
  cer0_ramp_type_sine_beginning        = 0x03,
  cer0_ramp_type_sine_ending           = 0x04
};

cer0_ramp_function_poll cer0_ramp_type_to_poll_function(
  enum cer0_ramp_type
);

float cer0_ramp_poll(
  enum cer0_ramp_type,
  float,
  float
);

float cer0_ramp_poll_linear(
  float,
  float
);

float cer0_ramp_poll_sine(
  float,
  float
);

float cer0_ramp_poll_sine_beginning_ending(
  float,
  float
);

float cer0_ramp_poll_sine_beginning(
  float,
  float
);

float cer0_ramp_poll_sine_ending(
  float,
  float
);

#endif
