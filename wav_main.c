#include "wav_head.h"
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// get rid of these functions later
double melody1(double note, int i, int offset) {
	if ((i < 10980 + offset) || (i > 12990 + offset && i < 15990 + offset) ||
		(i > 39990 + offset && i < 54000 + offset) ||
		(i > 60000 + offset && i < 63990 + offset)) {
		note = E4;
	} else if ((i > 19980 + offset && i < 22980 + offset) ||
			   (i > 54000 + offset && i < 57000 + offset)) {
		note = D4;
	} else if ((i > 27000 + offset && i < 30000 + offset)) {
		note = G4;
	} else if ((i > 33990 + offset && i < 36990 + offset)) {
		note = A4;
	} else if ((i > 66990 + offset && i < 69990 + offset) ||
			   (i > 87000 + offset && i < 90000 + offset)) {
		note = C4;
	} else if ((i > 73980 + offset && i < 84000 + offset) ||
			   (i > 93990 + offset && i < 103980 + offset)) {
		note = B3;
	} else {
		note = 0;
	}
	return note;
}

double melody2(double note, int i) {
	if ((i > 283980 && i < 292980) || (i > 333990 && i < 337980)) {
		note = E4;
	} else if ((i > 294000 && i < 315990) || (i > 337980 && i < 348000)) {
		note = D4;
	} else if ((i > 213990 && i < 231990) || (i > 234000 && i < 238980) ||
			   (i > 321000 && i < 333990)) {
		note = G4;
	} else if ((i > 240990 && i < 246000) || (i > 267000 && i < 280980)) {
		note = A4;
	} else if ((i > 280980 && i < 283980)) {
		note = G4B;
	} else if ((i > 246990 && i < 265980)) {
		note = B4;
	} else if ((i > 348000 && i < 373980)) {
		note = C4;
	} else {
		note = 0;
	}
	return note;
}

int main(void) {
	FILE *fw;
	wavHeader wav_h = {0};
	wav_h = populateHead(wav_h);
	__uint32_t dataBuffer[DATA_BUFFER_SIZE];
	double note = E4;

	if ((fw = fopen("melody.wav", "w")) == NULL) {
		printf("can't open\n");
		return 1;
	}
	fwrite(&wav_h, 1, sizeof(wavHeader), fw);

	for (int i = 0; i < DATA_BUFFER_SIZE; i++) {
		dataBuffer[i] = (sin((2 * M_PI * i * note) / FREQUENCY) * AMPLITUDE);
		// very ugly, not pretty at all, gotta improve later
		if (i < 103980) {
			note = melody1(note, i, 0);
		} else if (i > 106980 && i < 213990) {
			note = melody1(note, i, 106980);
		} else if (i > 213990) {
			note = melody2(note, i);
		}
	}
	fwrite(dataBuffer, 2, DATA_BUFFER_SIZE, fw);

	if (fclose(fw) == EOF) {
		printf("can't close\n");
		return 2;
	}

	return 0;
}
