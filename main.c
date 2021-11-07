#include <stdlib.h>
#include <stdio.h>

#include "audiofilter.h"

void usage(void) {
    printf("Program usage:\n");
    printf("noise_remover <audio_file.wav>");
}

int main(int argc, char *argv[]) {
    puts("Started");
    filter_init(
        "/Users/dominik/Desktop/Code/C/NoiseReduction/audio_u8_2.wav",
        "/Users/dominik/Desktop/Code/Other/out/filtered.wav"
    );
    run_process();
    filter_destroy();
    return EXIT_SUCCESS;
}