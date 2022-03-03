#include "stif.h"

#include <math.h>
#include <stdlib.h>

#include "histogram.h"

static float
mean(float* const histogram)
{
    histogram_normalize(histogram);

    float mean = 0.f;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        mean += histogram[i] * i;

    free(histogram);
    return mean;
}

float stif_mean(const unsigned char* const channel, const int size)
{
    float* const histogram = histogram_make(channel, size);
    return mean(histogram);
}

float stif_lmean(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width)
{
    float* const histogram = histogram_make_local(channel, width, height, i, j, half_width);
    return mean(histogram);
}

static int
median(float* const histogram)
{
    for (int i = 0; i < HISTOGRAM_NLEV; i++) {
        float l = 0.f, r = 0.f;
        for (int j = 0; j <= i; j++)
            l += histogram[i];
        for (int j = 0; j < HISTOGRAM_NLEV; j++)
            r += histogram[i] / 2;
        if (l >= r) {
            free(histogram);
            return i;
        }
    }

    free(histogram);
    return -1;
}

int stif_median(const unsigned char* const channel, const int size)
{
    float* const histogram = histogram_make(channel, size);
    return median(histogram);
}

int stif_lmedian(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width)
{
    float* const histogram = histogram_make_local(channel, width, height, i, j, half_width);
    return median(histogram);
}

static float
variance(float* const histogram, const float mean)
{
    histogram_normalize(histogram);

    float variance = 0.f;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        variance += histogram[i] * pow(i - mean, 2);

    free(histogram);
    return variance;
}

float stif_variance(const unsigned char* const channel, const int size)
{
    float* const histogram = histogram_make(channel, size);
    const float mean = stif_mean(channel, size);
    return variance(histogram, mean);
}

float stif_lvariance(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width)
{
    float* const histogram = histogram_make_local(channel, width, height, i, j, half_width);
    const float mean = stif_lmean(channel, width, height, i, j, half_width);
    return variance(histogram, mean);
}

static float
entropy(float* const histogram)
{
    histogram_normalize(histogram);

    float entropy = 0.f;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        entropy -= histogram[i] * log2(histogram[i]);

    free(histogram);
    return entropy;
}

float stif_entropy(const unsigned char* const channel, const int size)
{
    float* const histogram = histogram_make(channel, size);
    return entropy(histogram);
}

float stif_lentropy(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width)
{
    float* const histogram = histogram_make_local(channel, width, height, i, j, half_width);
    return entropy(histogram);
}
