CC = gcc
OBJ = audiofilter.o audiofile.o signal_processing.o
FLAGS = -I

audio_filter: $(OBJ)
	$(CC) -o $@ $^ main.c

audiofilter.o: audiofilter.c audiofilter.h
	$(CC) -c -o $@ $< $(FLAGS) audiofilter.h

signal_processing.o: signal_processing.c signal_processing.h
	$(CC) -c -o $@ $< $(FLAGS) signal_processing.h

audio_file.o: audiofile.c audiofile.h
	$(CC) -c -o $@ $< $(FLAGS)

clean:
	rm *.o
	echo "Clean"