#include "melody.h"
#include "wav_head.h"

int main(void) {
	FILE *fw;
	wavHeader wav_h = {0};
	wavHeader *pHeader = &wav_h;
	populateHead(pHeader);
	noteDuration melody[37] = {0};
	int len = sizeof(melody) / sizeof(melody[0]), j = 0;
	unsigned int dataBuffer[DATA_BUFFER_SIZE];
	if (!laFemme(melody, len)) {
		return 1;
	}
	double currNote = melody[0].note;

	if ((fw = fopen("melody.wav", "w")) == NULL) {
		fprintf(stderr, "can't open\n");
		return 2;
	}
	fwrite(&wav_h, 1, sizeof(wavHeader), fw);

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
		return 3;
	}

	return 0;
}
