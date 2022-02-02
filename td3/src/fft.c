#include "fft.h"

#include <math.h>
#include <fftw3.h>
#include <stdlib.h>

static fftw_complex*
conv_uchar_to_complex(unsigned char* channel, int width, int height)
{
    fftw_complex* c_channel = (fftw_complex *)fftw_malloc(width*height*sizeof(double));

    // Centering and normalizing
    char sign;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            sign = (x+y)%2 == 0 ? 1 : -1;
            c_channel[x*width+y] = sign * (float)channel[x*width+y] / (width*height);
        }
    
    return c_channel;
}

static unsigned char*
conv_complex_to_uchar(fftw_complex* c_channel, int width, int height)
{
    unsigned char* channel = (unsigned char*) malloc(width*height*sizeof(unsigned char));
    
    // Decentering
    char sign;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++)
        {
            sign = (x+y)%2 == 0 ? 1 : -1;
            channel[x*width+y] = sign * c_channel[x*width+y];
        }

    return channel;
}


fftw_complex*
fft_forward(unsigned char* chan, int width, int height)
{
    fftw_complex* out = (fftw_complex *)fftw_malloc(width*height*sizeof(double));
    fftw_complex* in = conv_uchar_to_complex(chan, width, height);
    fftw_plan plan = fftw_plan_dft_2d(height, width, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_free(in);
    return out;
}

unsigned char*
fft_backward(fftw_complex* fr_chan, int width, int height)
{
    fftw_complex* out = (fftw_complex *)fftw_malloc(width*height*sizeof(double));
    fftw_complex* in = conv_complex_to_uchar(fr_chan, width, height);
    fftw_plan plan = fftw_plan_dft_2d(height, width, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftw_execute(plan);
    fftw_destroy_plan(plan);
    fftw_free(in);
    return out;
}
