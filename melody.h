#include "wav_head.h"

#ifndef MELODY
#define MELODY

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define B3 246.94
#define C4 261.63
#define D4 293.66
#define E4 329.63
#define G4B 369.99
#define G4 392.00
#define A4 440.00
#define B4 493.88

typedef struct {
	double note;
	double start;
	double end;
} noteDuration;

bool laFemme(noteDuration arr[], int len);

#endif
