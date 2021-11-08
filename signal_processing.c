#include "signal_processing.h"

filter_options opts;

uint16_t get_frequency(uint32_t index, uint32_t sample_rate) {
    double_t multiplier = (double_t) (sample_rate / (double_t) BUFF_SIZE);
    uint16_t frequency = (double_t) index * multiplier;
    if (frequency > (sample_rate / 2))
        frequency = sample_rate - frequency;
    return frequency;
}

void signal_filter(Complex data_freq_domain[], uint32_t sample_rate) {
    for (uint32_t i = 1; i < BUFF_SIZE; i++) {
        double_t magnitude = sqrt(pow(creal(data_freq_domain[i]), 2) + pow(cimag(data_freq_domain[i]), 2));
        uint16_t freq = get_frequency(i, sample_rate);
        if (freq >= opts.freq_from && freq <= opts.freq_to) {
            if (opts.verbose)
                printf("Frequency to remove: %dHz, magnitude: %g\n", freq, magnitude);
            data_freq_domain[i] = 0.0 + I * 0;
        }
    }
}

void hamming_window(sample_t *samples, uint32_t N) {
    int i;
    for (i = 0; i < N; i++) {
        samples[i] *= (0.53836f - 0.46164f * cos((2 * M_PI * i) / (N - 1)));
    }
}

/* Fast Fourier Transform */
void fft(const double_t input_data[], Complex output_data[], uint32_t step, uint32_t N) {
    if (N == 1) {
        output_data[0] = input_data[0];
    } else {
        fft(input_data, output_data, step * 2, N / 2);
        fft(input_data + step, output_data + N / 2, step * 2, N / 2);

        uint32_t k;
        for (k = 0; k < N / 2; k++) {
            Complex p = output_data[k];
            Complex q = output_data[k + N / 2] * cexp(-2 * I * M_PI / N * k);
            output_data[k] = p + q;
            output_data[k + N / 2] = p - q;
        }
    }
}

/* Inverse Fast Fourier Transform */
static void _ifft(const Complex input_data[], Complex output_data[], uint32_t step, uint32_t N) {
    if (N == 1) {
        output_data[0] = input_data[0];
    } else {
        _ifft(input_data, output_data, step * 2, N / 2);
        _ifft(input_data + step, output_data + N / 2, step * 2, N / 2);

        uint32_t k;
        for (k = 0; k < N / 2; k++) {
            Complex p = output_data[k];
            Complex q = output_data[k + N / 2] * cexp(2 * I * M_PI / N * k);
            output_data[k] = p + q;
            output_data[k + N / 2] = p - q;
        }
    }
}

void ifft(const Complex input_data[], Complex output_data[], uint32_t N) {
    _ifft(input_data, output_data, 1, N);
    for(int i = 0; i < N; i++) {
        output_data[i] /= N;
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
