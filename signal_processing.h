#include <math.h>
#include <stdint.h>
#include <complex.h>
#include <stdio.h>

#define BUFF_SIZE 131072U
typedef double complex Complex;
typedef uint8_t sample_t;

typedef struct {
    uint32_t freq_from;
    uint32_t freq_to;
    uint8_t verbose;
} filter_options;

uint16_t get_frequency(uint32_t, uint32_t);
void signal_filter(Complex[], uint32_t);
void hamming_window(sample_t*, uint32_t);
void fft(const double_t[], Complex[], uint32_t, uint32_t);
void ifft(const Complex[], Complex [], uint32_t);
void show(Complex[], uint8_t);
static void _ifft(const Complex[], Complex[], uint32_t, uint32_t);

extern filter_options opts;