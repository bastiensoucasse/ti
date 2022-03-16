#include "histogram.h"

#include <stdio.h>
#include <stdlib.h>

#include "bbox.h"

static float*
histogram_create()
{
    float* hist = (float*)malloc(HISTOGRAM_NLEV * sizeof(float));
    if (!hist) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return hist;
}

static void
histogram_init(float* hist)
{
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        hist[i] = 0.f;
}

static float
get_size_from_histogram(float* hist)
{
    float size = 0.f;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        size += hist[i];
    return size;
}

float*
histogram_make(unsigned char* channel, int size)
{
    float* hist = histogram_create();
    histogram_init(hist);

    for (int p = 0; p < size; p++)
        hist[channel[p]]++;

    return hist;
}

float*
histogram_make_local(unsigned char* channel, int width, int height, int i, int j, int half_width)
{
    float* hist = histogram_create();
    histogram_init(hist);

    struct bbox box = bbox_init(width, height, i, j, half_width);
    for (int i = box.imin; i <= box.imax; i++)
        for (int j = box.jmin; j <= box.jmax; j++)
            hist[channel[i * width + j]]++;

    return hist;
}

float*
histogram_tdup(float* hist)
{
    float* dup = histogram_create();
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        dup[i] = hist[i];
    return dup;
}

void histogram_cumulate(float* hist)
{
    for (int i = 1; i < HISTOGRAM_NLEV; i++)
        hist[i] += hist[i - 1];
}

void histogram_normalize(float* hist)
{
    float size = get_size_from_histogram(hist);
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        hist[i] /= size;
}
