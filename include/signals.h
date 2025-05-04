#ifndef signals_h
#define signals_h

#include "constants.h"

extern unsigned int SIGNAL_COUNT;

typedef float (*SignalFunction)(float);

float SignalSine(float);
float SignalWhiteNoise(float);
float SignalSawtoothUp(float);
float SignalSawtoothDown(float);
float SignalSquare(float);
float SignalTriangle(float);

extern char *SignalNameLookup[6];
extern SignalFunction SignalFunctionLookup[6];

#endif
