#include "stif.h"

#include <math.h>
#include <stdlib.h>

#include "histogram.h"

static float
mean(float* hist)
{
    histogram_normalize(hist);

    float mean = 0;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        mean += hist[i] * i;

    free(hist);
    return mean;
}

float stif_mean(unsigned char* channel, int size)
{
    float* hist = histogram_make(channel, size);
    return mean(hist);
}

// float stif_lmean(unsigned char* channel, int width, int height, int i, int j, int half_width)
// {
//     float* hist = histogram_make_local(channel, width, height, i, j, half_width);
//     return mean(hist);
// }

static int
median(float* hist)
{
    for (int i = 0; i < HISTOGRAM_NLEV; i++) {
        float l = 0, r = 0;
        for (int j = 0; j <= i; j++)
            l += hist[j];
        for (int j = 0; j < HISTOGRAM_NLEV; j++)
            r += hist[j] / 2;
        if (l >= r) {
            free(hist);
            return i;
        }
    }

    free(hist);
    return -1;
}

int stif_median(unsigned char* channel, int size)
{
    float* hist = histogram_make(channel, size);
    return median(hist);
}

// int stif_lmedian(unsigned char* channel, int width, int height, int i, int j, int half_width)
// {
//     float* hist = histogram_make_local(channel, width, height, i, j, half_width);
//     return median(hist);
// }

static float
variance(float* hist, float mean)
{
    histogram_normalize(hist);

    float variance = 0;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        variance += hist[i] * pow(i - mean, 2);

    free(hist);
    return variance;
}

float stif_variance(unsigned char* channel, int size)
{
    float* hist = histogram_make(channel, size);
    float mean = stif_mean(channel, size);
    return variance(hist, mean);
}

// float stif_lvariance(unsigned char* channel, int width, int height, int i, int j, int half_width)
// {
//     float* hist = histogram_make_local(channel, width, height, i, j, half_width);
//     float mean = stif_lmean(channel, width, height, i, j, half_width);
//     return variance(hist, mean);
// }

static float
entropy(float* hist)
{
    histogram_normalize(hist);

    float entropy = 0;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        if (hist[i] != 0)
            entropy -= hist[i] * log2(hist[i]);

    free(hist);
    return entropy;
}

float stif_entropy(unsigned char* channel, int size)
{
    float* hist = histogram_make(channel, size);
    return entropy(hist);
}

// float stif_lentropy(unsigned char* channel, int width, int height, int i, int j, int half_width)
// {
//     float* hist = histogram_make_local(channel, width, height, i, j, half_width);
//     return entropy(hist);
// }
