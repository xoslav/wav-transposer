#ifndef WAV_HEAD_H
#define WAV_HEAD_H

#define BLOCK_SIZE 16
#define AUDIO_FORMAT 1
#define NBR_CHANNELS 1
#define FREQUENCY 60000
#define BITS_PER_SAMPLE 16
#define TIME_LENGTH 13
#define DATA_BUFFER_SIZE TIME_LENGTH *FREQUENCY
#define AMPLITUDE 45000

// maybe move later
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

wavHeader populateHead(wavHeader header);
#endif
