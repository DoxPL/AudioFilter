#include "audiofile.h"
#include "signal_processing.h"

#define FILE_PATH_BUFF_SIZE 512
#define INCORRECT_ARG 10
#define INIT_SUCCESS 0
#define INIT_IO_ERROR 20
#define INIT_UNSUPPORTED_AUDIO_FORMAT 21

typedef struct {
    FILE *file_in;
    FILE *file_out;
    wav_meta file_meta;
    double_t multiplier;
} audio_filter;

uint8_t filter_init(const char*, const char*);
void filter_destroy(void);
void run_process(void);
