#include "audiofilter.h"

static audio_filter filter;
static _complex_ out_buffer[BUFF_SIZE];
static _complex_ fft_buffer[BUFF_SIZE];
static double_t data_double[BUFF_SIZE];

void filter_init(const char *filename_in, const char *filename_out) {
    filter.file_in = open_audio_read(filename_in);
    filter.file_out = open_audio_write(filename_out);
    if (filename_in == NULL || filename_out == NULL) {
        return;
    }

    clone_audio_meta(&filter.file_meta, filter.file_in, filter.file_out);
}

void filter_destroy(void) {
    fclose(filter.file_in);
    fclose(filter.file_out);
}

void run_process() {
    while (!feof(filter.file_in)) {
        read_audio(filter.file_in, data_double, BUFF_SIZE);
        fft(data_double, fft_buffer, 1, BUFF_SIZE);
        signal_filter(
            fft_buffer, filter.file_meta.fmt.fmt_sample_rate
        );
        ifft(fft_buffer, out_buffer, BUFF_SIZE);
        write_audio(out_buffer, filter.file_out);
    }
}
