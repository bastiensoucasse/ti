#include "threshold.h"

#include <math.h>
#include <stdlib.h>

#include "histogram.h"
#include "stif.h"

unsigned char*
threshold_std(unsigned char* channel, int size, unsigned char th)
{
    for (int p = 0; p < size; p++)
        if (channel[p] < th)
            channel[p] = 0;
        else
            channel[p] = HISTOGRAM_NLEV - 1;
    return channel;
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
    /// TODO: Fix.

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            unsigned char th = (unsigned char)round(stif_lmean(channel, width, height, i, j, half_width));
            if (channel[i * width + j] < th)
                channel[i * width + j] = 0;
            else
                channel[i * width + j] = HISTOGRAM_NLEV - 1;
        }
    return channel;
}

unsigned char*
threshold_percent(unsigned char* channel, int size, float percent)
{
    /// TODO: Fix.

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
