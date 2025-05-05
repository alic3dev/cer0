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

  if (phaseValue >= CER0_TWO_PI) {
    phaseValue -= CER0_TWO_PI;
  }

  if (phaseValue < 0.0f) {
    phaseValue += CER0_TWO_PI;
  }

  return phaseValue;
}
