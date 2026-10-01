#include "wav_head.h"
#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(void) {
	FILE *fw;
	wavHeader wav_h = {0};
	wavHeader *pHeader = &wav_h;
	populateHead(pHeader);
	// I'd like to initialize this in a fuction
	noteDuration melody[37] = {
		[0].note = E4,	 [0].start = 0,		  [0].end = 0.366,
		[1].note = E4,	 [1].start = 0.433,	  [1].end = 0.533,
		[2].note = D4,	 [2].start = 0.666,	  [2].end = 0.766,
		[3].note = G4,	 [3].start = 0.9,	  [3].end = 1.0,
		[4].note = A4,	 [4].start = 1.133,	  [4].end = 1.233,
		[5].note = E4,	 [5].start = 1.333,	  [5].end = 1.8,
		[6].note = D4,	 [6].start = 1.8,	  [6].end = 1.9,
		[7].note = E4,	 [7].start = 2.0,	  [7].end = 2.133,
		[8].note = C4,	 [8].start = 2.233,	  [8].end = 2.333,
		[9].note = B3,	 [9].start = 2.466,	  [9].end = 2.8,
		[10].note = C4,	 [10].start = 2.9,	  [10].end = 3.0,
		[11].note = B3,	 [11].start = 3.133,  [11].end = 3.466,
		[12].note = E4,	 [12].start = 3.566,  [12].end = 3.933,
		[13].note = E4,	 [13].start = 4.0,	  [13].end = 4.1,
		[14].note = D4,	 [14].start = 4.233,  [14].end = 4.333,
		[15].note = G4,	 [15].start = 4.466,  [15].end = 4.566,
		[16].note = A4,	 [16].start = 4.7,	  [16].end = 4.8,
		[17].note = E4,	 [17].start = 4.9,	  [17].end = 5.366,
		[18].note = D4,	 [18].start = 5.366,  [18].end = 5.466,
		[19].note = E4,	 [19].start = 5.566,  [19].end = 5.7,
		[20].note = C4,	 [20].start = 5.8,	  [20].end = 5.9,
		[21].note = B3,	 [21].start = 6.033,  [21].end = 6.366,
		[22].note = C4,	 [22].start = 6.466,  [22].end = 6.566,
		[23].note = B3,	 [23].start = 6.7,	  [23].end = 7.033,
		[24].note = G4,	 [24].start = 7.133,  [24].end = 7.766,
		[25].note = G4,	 [25].start = 7.8,	  [25].end = 7.966,
		[26].note = A4,	 [26].start = 8.033,  [26].end = 8.2,
		[27].note = B4,	 [27].start = 8.233,  [27].end = 8.866,
		[28].note = A4,	 [28].start = 8.9,	  [28].end = 9.366,
		[29].note = G4B, [29].start = 9.366,  [29].end = 9.466,
		[30].note = E4,	 [30].start = 9.466,  [30].end = 9.766,
		[31].note = D4,	 [31].start = 9.8,	  [31].end = 10.533,
		[32].note = G4,	 [32].start = 10.7,	  [32].end = 11.133,
		[33].note = E4,	 [33].start = 11.133, [33].end = 11.266,
		[34].note = D4,	 [34].start = 11.266, [34].end = 11.6,
		[35].note = C4,	 [35].start = 11.6,	  [35].end = 12.466,
		[36].note = 0.0, [36].start = 12.466, [36].end = 13.0,
	};
	unsigned int dataBuffer[DATA_BUFFER_SIZE];
	int j = 0;
	double currNote = melody[0].note;

	if ((fw = fopen("melody.wav", "w")) == NULL) {
		fprintf(stderr, "can't open\n");
		return 1;
	}
	fwrite(&wav_h, 1, sizeof(wavHeader), fw);

	// i / 30000 = cas ve vterinach; najit jestli to neni mezi start a end noty

	for (int i = 0; i < DATA_BUFFER_SIZE; i++) {
		dataBuffer[i] = (sin((2 * M_PI * i * currNote) / FREQUENCY) * AMPLITUDE);
		if (i / 30000.0 > melody[j].end && i / 30000.0 < melody[j + 1].start) {
			currNote = 0.0;
		} else if (i / 30000.0 >= melody[j + 1].start) {
			j++;
			currNote = melody[j].note;
		}
	}
	fwrite(dataBuffer, 2, DATA_BUFFER_SIZE, fw);

	if (fclose(fw) == EOF) {
		fprintf(stderr, "can't close\n");
		return 2;
	}

	return 0;
}
