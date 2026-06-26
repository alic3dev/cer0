#include <cer0_pan.h>

#include <math_c_maximum.h>
#include <math_c_minimum.h>

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
    (
      0x01 -
      math_c_maximum_float(
        pan,
        0x00
      )
    ) *
    value
  );
  
  result[
    0x01
  ] = (
    (
      0x01 +
      math_c_minimum_float(
        pan,
        0x00
      )
    ) *
    value
  );
}
