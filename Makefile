CC = clang
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Werror -lm 
MAIN_DEPS = wav_main.c wav_head.c

main: $(MAIN_DEPS)
	$(CC) $(CFLAGS) $^ -o $@

run:
	./main

clean:
	rm main && rm melody.wav