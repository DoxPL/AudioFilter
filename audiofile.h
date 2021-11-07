#include <stdint.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>

#define BUFF_SIZE 131072U
#define OPEN_READ 0
#define OPEN_WRITE 1

typedef double complex Complex;
typedef uint8_t sample_t;

typedef struct {
    uint32_t chunk_id;
    uint32_t chunk_size;
    uint32_t format;
} wav_riff;

typedef struct {
    uint32_t fmt_chunk;
    uint32_t fmt_size;
    uint16_t fmt_audio_format;
    uint16_t fmt_num_channels;
    uint32_t fmt_sample_rate;
    uint32_t fmt_byte_rate;
    uint16_t fmt_block_align;
    uint16_t fmt_bp_sample;
} wav_fmt;

typedef struct {
    uint32_t data_id;
    uint32_t data_size;
} wav_scdata;

typedef struct {
    wav_riff riff;
    wav_fmt fmt;
    wav_scdata data;
} wav_meta;

FILE *open_audio_read(const char *);
FILE *open_audio_write(const char *);
void read_audio(FILE *, double_t*, const uint32_t);
void write_audio(const Complex *, FILE*);
void close_audio(FILE*);
float u8_to_float(uint8_t);
uint8_t float_to_u8(float);
uint32_t big_endian(uint32_t);
void print_riff(const wav_riff);
void print_fmt(const wav_fmt);
void print_scdata(const wav_scdata);
void clone_audio_meta(wav_meta*, FILE*, FILE*);

wav_meta audio_meta;
static uint16_t chunk_num = 0U;
static sample_t data_buffer[BUFF_SIZE];
//static uint32_t bytes_remaining = audio_meta.data.data_size;
//static double_t multiplier = subchunk.fmt_sample_rate / (double_t) BUFF_SIZE;

//@ToDo create if doesn't exists