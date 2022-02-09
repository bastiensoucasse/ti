#include "fft.h"

#include <math.h>
#include <stdlib.h>

static fftw_complex*
conv_uchar_to_complex(unsigned char* channel, int width, int height)
{
    fftw_complex* c_channel = (fftw_complex*)fftw_malloc(width * height * sizeof(fftw_complex));

    // Centering and normalizing
    char sign;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            sign = (i + j) % 2 == 0 ? 1 : -1;
            c_channel[i * width + j] = sign * (double)channel[i * width + j] / (width * height);
        }

    return c_channel;
}

static unsigned char*
conv_complex_to_uchar(fftw_complex* c_channel, int width, int height)
{
    unsigned char* channel = (unsigned char*)malloc(width * height * sizeof(unsigned char));

    // Decentering
    char sign;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            sign = (i + j) % 2 == 0 ? 1 : -1;
            // Thresholding
            int value = sign * creal(c_channel[i * width + j]);
            if (value < 0)
                value = 0;
            if (value > 255)
                value = 255;
            channel[i * width + j] = value;
        }

    return channel;
}

fftw_complex*
fft_forward(unsigned char* chan, int width, int height)
{
    fftw_complex* in = conv_uchar_to_complex(chan, width, height);
    fftw_complex* out = (fftw_complex*)fftw_malloc(width * height * sizeof(fftw_complex));
    fftw_plan plan = fftw_plan_dft_2d(height, width, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    fftw_execute(plan);

    fftw_destroy_plan(plan);
    fftw_free(in);
    return out;
}

unsigned char*
fft_backward(fftw_complex* fr_chan, int width, int height)
{
    fftw_complex* out = (fftw_complex*)fftw_malloc(width * height * sizeof(fftw_complex));
    fftw_plan plan = fftw_plan_dft_2d(height, width, fr_chan, out, FFTW_BACKWARD, FFTW_ESTIMATE);

    fftw_execute(plan);
    unsigned char* channel = conv_complex_to_uchar(out, width, height);

    fftw_destroy_plan(plan);
    fftw_free(out);
    return channel;
}

double*
fft_extract_as(fftw_complex* fr_chan, int width, int height)
{
    double* as = (double*)malloc(width * height * sizeof(double));
    for (unsigned int i = 0; i < width * height; i++)
        as[i] = sqrt(pow(creal(fr_chan[i]), 2) + pow(cimag(fr_chan[i]), 2));
    return as;
}

double*
fft_extract_ps(fftw_complex* fr_chan, int width, int height)
{
    double* ps = (double*)malloc(width * height * sizeof(double));
    for (int i = 0; i < width * height; i++)
        ps[i] = atan2(cimag(fr_chan[i]), creal(fr_chan[i]));
    return ps;
}

fftw_complex*
fft_compose_aps(double* as, double* ps, int width, int height)
{
    fftw_complex* fr_chan = (fftw_complex*)fftw_malloc(width * height * sizeof(fftw_complex));
    for (int i = 0; i < width * height; i++)
        fr_chan[i] = as[i] * cos(ps[i]) + as[i] * sin(ps[i]) * I;
    return fr_chan;
}
