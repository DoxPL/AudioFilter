#include "audiofile.h"
#include <stdio.h>

FILE *open_audio_read(const char *filename) {
    FILE *audio_file = fopen(filename, "rb");
    if (!audio_file) {
        puts("Cannot open file to read");
        return NULL;
    }
    return audio_file;
}

FILE *open_audio_write(const char *filename) {
    FILE *audio_file = fopen(filename, "wb");
    if (!audio_file) {
        puts("Cannot open file to write");
        return NULL;
    }
    return audio_file;
}

void read_audio(FILE *audio_file, double_t *out_buffer, const uint32_t bytes_to_read) {
    memset(&data_buffer, 0U, BUFF_SIZE);
    fread(data_buffer, bytes_to_read, 1, audio_file);
    for (int i=0; i < BUFF_SIZE; i++) {
        out_buffer[i] = u8_to_float(data_buffer[i]);
    }
}

void write_audio(const Complex *out_buffer, FILE *audio_file) {
    for (uint32_t i = 0; i < BUFF_SIZE; i++) {
        if (data_buffer[i] < 0)
            data_buffer[i] = (sample_t)(creal(out_buffer[i]) * 256.0 - 256) & 0xFF;
        else
            data_buffer[i] = (sample_t)(creal(out_buffer[i]) * 256.0) & 0xFF;
    }
    fwrite(data_buffer, sizeof(data_buffer), 1, audio_file);
}

void close_audio(FILE *audio_file) {
    fclose(audio_file);
}

float u8_to_float(uint8_t sample_u8) {
    float flt_value;
    flt_value = ((float) sample_u8) / 256.0;
    if(flt_value > 1.0)
        flt_value = 1.0;
    if(flt_value < -1.0)
        flt_value = -1.0;
    return flt_value;
}

//ToDo fix
uint8_t float_to_u8(float sample_flt) {
    uint8_t u8_value;
    // if (data_buffer[i] < 0)
    //     data_buffer[i] = (sample_t)(creal(out_buffer[i]) * 256.0 - 256) & 0xFF;
    // else
    //     data_buffer[i] = (sample_t)(creal(out_buffer[i]) * 256.0) & 0xFF;
    return u8_value;
}

uint32_t big_endian(uint32_t num) {
    uint32_t num_big_endian = 0U;
    num_big_endian |= (num << 24) & 0xFF000000;
    num_big_endian |= (num << 8) & 0xFF0000;
    num_big_endian |= (num >> 24) & 0xFF;
    num_big_endian |= (num >> 8) & 0xFF00;
    return num_big_endian;
}

void print_riff(const wav_riff riff) {
    printf("Chunk ID: %d\n", big_endian(riff.chunk_id));
    printf("Chunk size: %d\n", riff.chunk_size);
    printf("Format: %d\n", riff.format);
}

void print_subchunk(const wav_fmt fmt) {
    printf("FMT chunk: %d\n", fmt.fmt_chunk);
    printf("FMT size %u\n", fmt.fmt_size);
    printf("FMT audio format %hi\n", fmt.fmt_audio_format);
    printf("FMT channels: %hi\n", fmt.fmt_num_channels);
    printf("FMT sample rate %d\n", fmt.fmt_sample_rate);
    printf("FMT byte rate: %d\n", fmt.fmt_byte_rate);
    printf("FMT block align: %hi\n", fmt.fmt_block_align);
    printf("FMT bits per sample: %hi\n", fmt.fmt_bp_sample);
}

void print_scdata(const wav_scdata data) {
    printf("Data ID: %#08x\n", big_endian(data.data_id));
    printf("Data size: %d\n", data.data_size);
}

void clone_audio_meta(wav_meta *meta, FILE *in_file, FILE *out_file) {
    fread(&meta->riff, sizeof(wav_riff), 1, in_file);
    fwrite(&meta->riff, sizeof(wav_riff), 1, out_file);
    print_riff(meta->riff);

    fread(&meta->fmt, sizeof(wav_fmt), 1, in_file);
    fwrite(&meta->fmt, sizeof(wav_fmt), 1, out_file);
    print_subchunk(meta->fmt);

    fread(&meta->data, sizeof(wav_scdata), 1, in_file);
    fwrite(&meta->data, sizeof(wav_scdata), 1, out_file);
    print_scdata(meta->data);
    printf("Resolution: %d\n", meta->data.data_size / meta->fmt.fmt_sample_rate);
}