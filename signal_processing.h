#include <math.h>
#include <stdint.h>
#include <complex.h>
#include <stdio.h>

#define BUFF_SIZE 131072U
typedef double complex Complex;
typedef uint8_t sample_t;

uint16_t get_frequency(uint32_t, uint32_t);
void signal_filter(Complex[], const uint32_t, const uint32_t);
void hamming_window(sample_t*, const uint32_t);
void fft(double_t[], Complex[], uint32_t, const uint32_t);
void ifft(Complex[], Complex [], const uint32_t);
void show(Complex[], uint8_t);