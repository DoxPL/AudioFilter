#include "audiofile.h"
#include "signal_processing.h"

#define FILENAME_BUFF_SIZE 128

typedef struct {
    FILE *file_in;
    FILE *file_out;
    wav_meta file_meta;
    double_t multiplier;
} audio_filter;

void filter_init(const char*, const char*);
void filter_destroy(void);
void run_process();
