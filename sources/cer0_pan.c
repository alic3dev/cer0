#include <cer0_pan.h>

#include <math_c_maximum.h>
#include <math_c_minimum.h>

#ifndef cer0_pan_value_left
#define cer0_pan_value_left(\
  pan\
)\
  (\
    0x01 -\
    math_c_maximum_float(\
      pan,\
      0x00\
    )\
  )
#endif

#ifndef cer0_pan_value_right
#define cer0_pan_value_right(\
  pan\
)\
  (\
    0x01 +\
    math_c_minimum_float(\
      pan,\
      0x00\
    )\
  )
#endif

void cer0_pan_apply_stereo(
  float value,
  float pan,
  float result[
    0x02
  ]
) {
  result[
    0x00
  ] = (
    cer0_pan_value_left(
      pan
    ) *
    value
  );

  result[
    0x01
  ] = (
    cer0_pan_value_right(
      pan
    ) *
    value
  );
}

void cer0_pan_apply_stereo_pan(
  float value[
    0x02
  ],
  float pan
) {
  value[
    0x00
  ] = (
    value[
      0x00
    ] *
    cer0_pan_value_left(
      pan
    )
  );

  value[
    0x01
  ] = (
    value[
      0x01
    ] *
    cer0_pan_value_right(
      pan
    )
  );
}
