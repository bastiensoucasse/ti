#include "threshold.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"
#include "stif.h"

static unsigned char*
channel_malloc(int size)
{
    unsigned char* channel = (unsigned char*)malloc(size * sizeof(unsigned char));
    if (!channel) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return channel;
}

unsigned char*
threshold_std(unsigned char* channel, int size, unsigned char th)
{
    unsigned char* new_channel = channel_malloc(size);
    for (int p = 0; p < size; p++)
        new_channel[p] = channel[p] < th ? 0 : HISTOGRAM_NLEV - 1;
    return new_channel;
}

unsigned char*
threshold_mean(unsigned char* channel, int size)
{
    float mean = stif_mean(channel, size);
    return threshold_std(channel, size, (unsigned char)round(mean));
}

unsigned char*
threshold_median(unsigned char* channel, int size)
{
    int median = stif_median(channel, size);
    return threshold_std(channel, size, (unsigned char)median);
}

unsigned char*
threshold_lmean(unsigned char* channel, int width, int height, int half_width)
{
    unsigned char* new_channel = channel_malloc(width * height);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            unsigned char th = (unsigned char)stif_lmean(channel, width, height, i, j, half_width);
            new_channel[i * width + j] = channel[i * width + j] < th ? 0 : HISTOGRAM_NLEV - 1;
        }
    return new_channel;
}

unsigned char*
threshold_percent(unsigned char* channel, int size, float percent)
{
    float* histogram = histogram_make(channel, size);
    histogram_normalize(histogram);
    histogram_cumulate(histogram);

    int th = -1;
    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        if (histogram[i] > percent / 100) {
            th = i;
            break;
        }

    free(histogram);
    return threshold_std(channel, size, (unsigned char)th);
}
