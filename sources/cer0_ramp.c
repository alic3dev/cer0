#include <cer0_ramp.h>

#include <math_c_pi.h>
#include <math_c_sine.h>

cer0_ramp_function_poll cer0_ramp_type_to_poll_function(
  enum cer0_ramp_type cer0_ramp_type
) {
  switch (
    cer0_ramp_type
  ) {
    case cer0_ramp_type_sine: {
      return (
        cer0_ramp_poll_sine
      );
    }
    case cer0_ramp_type_sine_beginning_ending: {
      return (
        cer0_ramp_poll_sine_beginning_ending
      );
    }
    case cer0_ramp_type_sine_beginning: {
      return (
        cer0_ramp_poll_sine_beginning
      );
    }
    case cer0_ramp_type_sine_ending: {
      return (
        cer0_ramp_poll_sine_ending
      );
    }
    case cer0_ramp_type_linear:
    default: {
      return (
        cer0_ramp_poll_linear
      );
    }
  }
}

float cer0_ramp_poll(
  enum cer0_ramp_type cer0_ramp_type,
  float value,
  float percentage
) {
  cer0_ramp_function_poll cer0_ramp_function_poll = (
    cer0_ramp_type_to_poll_function(
      cer0_ramp_type
    )
  );

  return (
    cer0_ramp_function_poll(
      value,
      percentage
    )
  );
}

float cer0_ramp_poll_linear(
  float value,
  float percentage
) {
  return (
    value *
    percentage
  );
}

float cer0_ramp_poll_sine(
  float value,
  float percentage
) {
  float sine = (
    math_c_sine(
      (
        percentage *
        math_c_pi
      ),
      math_c_pi
    )
  );

  if (
    percentage >=
    0.5f
  ) {
    return (
      value *
      (
        0.5f +
        (
          (
            0x01 -
            sine
          ) /
          0x02
        )
      )
    );
  } else {
    return (
      value *
      sine /
      0x02
    );
  }
}

float cer0_ramp_poll_sine_beginning_ending(
  float value,
  float percentage
) {
  if (
    percentage <
    0.5f
  ) {
    return (
      cer0_ramp_poll_sine_beginning(
        value,
        percentage
      )
    );
  } else {
    return (
      cer0_ramp_poll_sine_ending(
        value,
        percentage
      )
    );
  }
}

float cer0_ramp_poll_sine_beginning(
  float value,
  float percentage
) {
  if (
    percentage >
    0.5f
  ) {
    return (
      value *
      percentage
    );
  }

  float sine = (
    0x01 -
    math_c_sine(
      (
        (
          0.5f -
          percentage
        ) /
        0.5f *
        math_c_pi_half
      ),
      math_c_pi
    )
  );

  return (
    value *
    sine /    0x02
  );
}

float cer0_ramp_poll_sine_ending(
  float value,
  float percentage
) {
  if (
    percentage <
    0.5f
  ) {
    return (
      value *
      percentage
    );
  }

  float sine = (
    math_c_sine(
      (
        (
          percentage -
          0.5f
        ) /
        0.5f *
        math_c_pi_half
      ),
      math_c_pi
    )
  );

  return (
    value /
    0x02 +
    value *
    sine /
    0x02
  );
}
