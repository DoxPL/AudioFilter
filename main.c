/*
 *     _          _ _     ___ _ _ _           
 *    /_\ _  _ __| (_)___| __(_) | |_ ___ _ _ 
 *   / _ \ || / _` | / _ \ _|| | |  _/ -_) '_|
 *  /_/ \_\_,_\__,_|_\___/_| |_|_|\__\___|_|  
 *
 * Author: Dominik G.
 * Version: 0.1 (alpha)
 * https://github.com/DoxPL
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "audiofilter.h"

void usage(void) {
    printf("Program usage:\n");
    printf("noise_remover -i <input_file> -o <output_file> ");
    printf("-f <from_frequency> -t <to_frequency> [-v]\n");
}

int main(int argc, char *argv[]) {
    int exit_code = EXIT_SUCCESS;
    char opt;
    char input_fn[FILE_PATH_BUFF_SIZE], output_fn[FILE_PATH_BUFF_SIZE];
    unsigned char mandatory_opts = 0U;

    while ((opt = getopt(argc, argv, "i:o:vf:t:")) != -1) {
        switch(opt) {
            case 'i':
                strcpy(input_fn, optarg);
                mandatory_opts++;
                break;
            case 'o':
                strcpy(output_fn, optarg);
                printf("%s\n", optarg);
                mandatory_opts++;
                break;
            case 'v':
                opts.verbose = 1;
                break;
            case 'f':
                opts.freq_from = atoi(optarg);
                mandatory_opts++;
                break;
            case 't':
                opts.freq_to = atoi(optarg);
                mandatory_opts++;
                break;
            default:
                usage();
                return INCORRECT_ARG;
        }
    }

    if (mandatory_opts < 4) {
        usage();
        return INCORRECT_ARG;
    }

    if (!(exit_code = filter_init(input_fn, output_fn))) {
        run_process();
        filter_destroy();
    }
    free_buff_mem();
    return exit_code;
}