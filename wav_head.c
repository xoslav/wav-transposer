#include "wav_head.h"

void populateHead(wavHeader *header) {
	strncpy(header->riffID, "RIFF", 4);
	strncpy(header->waveID, "WAVE", 4);
	strncpy(header->formatID, "fmt ", 4);
	strncpy(header->dataID, "data", 4);
	header->BlocSize = BLOCK_SIZE;
	header->AudioFormat = AUDIO_FORMAT;
	header->NbrChannels = NBR_CHANNELS;
	header->Frequency = FREQUENCY;
	header->BitsPerSample = BITS_PER_SAMPLE;
	header->BytePerBloc = (NBR_CHANNELS * BITS_PER_SAMPLE) / 8;
	header->BytePerSec = FREQUENCY * header->BytePerBloc;
	header->DataSize = DATA_BUFFER_SIZE * header->BytePerBloc;
	header->FileSize = header->DataSize + sizeof(wavHeader);
}
