#include "histogram.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "bbox.h"

float*
histogram_make(const unsigned char* const channel, const int size)
{
    float* histogram = (float*)malloc(HISTOGRAM_NLEV * sizeof(float));
    if (!histogram) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        histogram[i] = 0.f;

    for (int i = 0; i < size; i++)
        histogram[channel[i]]++;

    float n = 0;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        n += histogram[i];
    assert(n == size);

    return histogram;
}

float*
histogram_make_local(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width)
{
    float* histogram = (float*)malloc(HISTOGRAM_NLEV * sizeof(float));
    if (!histogram) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        histogram[i] = 0.f;

    const struct bbox bbox = bbox_init(width, height, i, j, half_width);
    for (int i = bbox.imin; i < bbox.imax; i++)
        for (int j = bbox.jmin; j < bbox.jmax; j++)
            histogram[channel[i * width + j]]++;

    return histogram;
}

float*
histogram_tdup(const float* const histogram)
{
    float* dup = (float*)malloc(HISTOGRAM_NLEV * sizeof(float));
    if (!histogram) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        dup[i] = histogram[i];

    return dup;
}

void histogram_cumulate(float* const histogram)
{
    for (int i = 1; i < HISTOGRAM_NLEV; i++)
        histogram[i] += histogram[i - 1];
}

void histogram_normalize(float* const histogram)
{
    int size = 0;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        size += histogram[i];

    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        histogram[i] /= size;

    float n = 0;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        n += histogram[i];
    assert(n == 1.);
}
