#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "audiofilter.h"
#define FILENAME_BUFF_SIZE 128

void usage(void) {
    puts("Program usage:");
    puts("noise_remover -i <input_file> -o <output_file> [-v]");
}

int main(int argc, char *argv[]) {
    char opt, flag_verbose;
    char input_fn[FILENAME_BUFF_SIZE], output_fn[FILENAME_BUFF_SIZE];
    (void) flag_verbose;

    if (argc < 3) {
        usage();
        return EXIT_FAILURE;
    }

    while ((opt = getopt(argc, argv, "i:o:v")) != -1) {
        switch(opt) {
            case 'i':
                strcpy(input_fn, optarg);
                break;
            case 'o':
                strcpy(output_fn, optarg);
                break;
            case 'v':
                flag_verbose = 1;
                break;
            default:
                usage();
                return EXIT_FAILURE;
        }
    }

    filter_init(input_fn, output_fn);
    run_process();
    filter_destroy();
    return EXIT_SUCCESS;
}