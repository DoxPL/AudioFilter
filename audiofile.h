#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <complex.h>
#include <libgen.h>
#include <sys/stat.h>

#define BUFF_SIZE 131072U
#define DIR_EXISTS 1
#define DIR_NOT_FOUND 0
#define DIR_PREPARED 0
#define DIR_NOT_PREPARED 1

typedef double complex _complex_;
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
void write_audio(const _complex_ *, FILE*);
void close_audio(FILE*);
void clone_audio_meta(wav_meta*, FILE*, FILE*);
static void print_riff(const wav_riff);
static void print_fmt(const wav_fmt);
static void print_scdata(const wav_scdata);
static float u8_to_float(uint8_t);
static uint8_t double_to_u8(double_t, uint32_t);
static uint32_t big_endian(uint32_t);
static uint8_t dir_exists(const char *);
static uint8_t prepare_dir(const char *);