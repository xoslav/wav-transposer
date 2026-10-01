#ifndef WAV_HEAD_H
#define WAV_HEAD_H

#include <string.h>

#define BLOCK_SIZE 16
#define AUDIO_FORMAT 1
#define NBR_CHANNELS 1
#define FREQUENCY 60000
#define BITS_PER_SAMPLE 16
#define TIME_LENGTH 13
#define DATA_BUFFER_SIZE TIME_LENGTH *FREQUENCY
#define AMPLITUDE 45000

typedef struct {
	char riffID[4];
	unsigned int FileSize;
	char waveID[4];
	char formatID[4];
	unsigned int BlocSize;
	unsigned short AudioFormat;
	unsigned short NbrChannels;
	unsigned int Frequency;
	unsigned int BytePerSec;
	unsigned short BytePerBloc;
	unsigned short BitsPerSample;
	char dataID[4];
	unsigned int DataSize;
} wavHeader;

void populateHead(wavHeader *header);

#endif
