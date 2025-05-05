#ifndef signals_h
#define signals_h

#include "constants.h"

#define CER0_SIGNALS_LENGTH 6

typedef float (*SignalFunction)(float);

float SignalSine(float);
float SignalWhiteNoise(float);
float SignalSawtoothUp(float);
float SignalSawtoothDown(float);
float SignalSquare(float);
float SignalTriangle(float);

extern char *SignalNameLookup[CER0_SIGNALS_LENGTH];
extern SignalFunction SignalFunctionLookup[CER0_SIGNALS_LENGTH];

#endif
