#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279
#endif

#define BLOCK_SIZE 16
#define AUDIO_FORMAT 1
#define NBR_CHANNELS 1
#define FREQUENCY 60000
#define BITS_PER_SAMPLE 16
#define TIME_LENGTH 13
#define DATA_BUFFER_SIZE TIME_LENGTH *FREQUENCY
#define AMPLITUDE 45000

#define B3 246.94
#define C4 261.63
#define D4 293.66
#define E4 329.63
#define G4B 369.99
#define G4 392.00
#define A4 440.00
#define B4 493.88

typedef struct {
	char riffID[4];
	__uint32_t FileSize;
	char waveID[4];
	char formatID[4];
	__uint32_t BlocSize;
	__uint16_t AudioFormat;
	__uint16_t NbrChannels;
	__uint32_t Frequency;
	__uint32_t BytePerSec;
	__uint16_t BytePerBloc;
	__uint16_t BitsPerSample;
	char dataID[4];
	__uint32_t DataSize;
} wavHeader;

wavHeader populateHead(wavHeader header) {
	strncpy(header.riffID, "RIFF", 4);
	strncpy(header.waveID, "WAVE", 4);
	strncpy(header.formatID, "fmt ", 4);
	strncpy(header.dataID, "data", 4);
	header.BlocSize = BLOCK_SIZE;
	header.AudioFormat = AUDIO_FORMAT;
	header.NbrChannels = NBR_CHANNELS;
	header.Frequency = FREQUENCY;
	header.BitsPerSample = BITS_PER_SAMPLE;
	header.BytePerBloc = (NBR_CHANNELS * BITS_PER_SAMPLE) / 8;
	header.BytePerSec = FREQUENCY * header.BytePerBloc;
	header.DataSize = DATA_BUFFER_SIZE * header.BytePerBloc;
	header.FileSize = header.DataSize + sizeof(wavHeader);

	return header;
}

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
