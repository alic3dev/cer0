#include "phase.h"

#include <math.h>
#include <stdio.h>

float PhaseGetIncrement(
  float sampleRate,
  float frequency
) {
  return ((M_PI * 2.0f) / sampleRate) * frequency;
}

float PhaseAdvance(
  float phaseValue,
  float phaseIncrement
) {
  phaseValue += phaseIncrement;

  if (phaseValue >= TWO_PI) {
    phaseValue -= TWO_PI;
  }

  if (phaseValue < 0.0f) {
    phaseValue += TWO_PI;
  }

  return phaseValue;
}
