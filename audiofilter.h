#include "audiofile.h"
#include "signal_processing.h"

typedef struct {
    FILE *file_in;
    FILE *file_out;
    wav_meta file_meta;
    double_t multiplier;
} audio_filter;

void filter_init(const char*, const char*);
void filter_destroy(void);
void run_process(void);

static audio_filter filter;
static Complex out_buffer[BUFF_SIZE];
static Complex fft_buffer[BUFF_SIZE];
static double_t data_double[BUFF_SIZE];