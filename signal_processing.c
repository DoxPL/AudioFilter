#include "signal_processing.h"

uint16_t get_frequency(uint32_t index, uint32_t sample_rate) {
    double_t multiplier = (double_t) (sample_rate / (double_t) BUFF_SIZE);
    uint16_t frequency = (double_t) index * multiplier;
    if (frequency > (sample_rate / 2))
        frequency = sample_rate - frequency;
    return frequency;
}

void signal_filter(Complex data_freq_domain[], const uint32_t sample_rate, const uint32_t sample_count) {
    for (uint32_t i = 1; i < sample_count; i++) {
        double_t magnitude = sqrt(pow(creal(data_freq_domain[i]), 2) + pow(cimag(data_freq_domain[i]), 2));
        uint16_t freq = get_frequency(i, sample_rate);
        if (freq > 890 && freq < 950) {
            printf("Freq to remove: %dHz, magnitude: %g\n", freq, magnitude);
            data_freq_domain[i] = 0.0 + I * 0;
        }
    }
}

void hamming_window(sample_t *samples, const uint32_t N) {
    int i;
    for (i = 0; i < N; i++) {
        samples[i] *= (0.53836f - 0.46164f * cos((2 * M_PI * i) / (N - 1)));
    }
}

/* Fast Fourier Transform */
void fft(double_t inputData[], Complex outputData[], uint32_t step, const uint32_t N) {
    if (N == 1) {
        outputData[0] = inputData[0];
    } else {
        fft(inputData, outputData, step * 2, N / 2);
        fft(inputData + step, outputData + N / 2, step * 2, N / 2);

        uint32_t k;
        for (k = 0; k < N / 2; k++) {
            Complex p = outputData[k];
            Complex q = outputData[k + N / 2] * cexp(-2 * I * M_PI / N * k);
            outputData[k] = p + q;
            outputData[k + N / 2] = p - q;
        }
    }
}

/* Inverse Fast Fourier Transform */
static void _ifft(Complex inputData[], Complex outputData[], uint32_t step, const uint32_t N) {
    if (N == 1) {
        outputData[0] = inputData[0];
    } else {
        _ifft(inputData, outputData, step * 2, N / 2);
        _ifft(inputData + step, outputData + N / 2, step * 2, N / 2);

        uint32_t k;
        for (k = 0; k < N / 2; k++) {
            Complex p = outputData[k];
            Complex q = outputData[k + N / 2] * cexp(2 * I * M_PI / N * k);
            outputData[k] = p + q;
            outputData[k + N / 2] = p - q;
        }
    }
}

void ifft(Complex inputData[], Complex outputData[], const uint32_t N) {
    _ifft(inputData, outputData, 1, N);
    for(int i = 0; i < N; i++) {
        outputData[i] /= N;
    }
}

void show(Complex buf[], uint8_t mode) {
    if (mode) {
        for (int i = 0; i < BUFF_SIZE; i++)
            if (!cimag(buf[i]))
                printf("%g ", creal(buf[i]));
            else
                printf("(%g, %g) ", creal(buf[i]), cimag(buf[i]));
    } else {
        for (int i = 0; i < BUFF_SIZE; i++) {
            printf("%g\n", creal(buf[i]));
        }
    }
}
