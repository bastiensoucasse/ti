#include "threshold.h"

#include <math.h>
#include <string.h>
#include <string.h>

#include "histogram.h"
#include "stif.h"

unsigned char*
threshold_std(const unsigned char* const channel, const int size, const unsigned char th)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, size);

    for (int i = 0; i < size; i++)
        if (channel[i] < th)
            out[i] = 0;
        else
            out[i] = 1;

    return out;
}

unsigned char*
threshold_mean(const unsigned char* const channel, const int size)
{
    const float mean = stif_mean(channel, size);
    return threshold_std(channel, size, (unsigned char)round(mean));
}

unsigned char*
threshold_median(const unsigned char* const channel, const int size)
{
    const int median = stif_median(channel, size);
    return threshold_std(channel, size, (unsigned char)median);
}

unsigned char*
threshold_lmean(const unsigned char* const channel, const int width, const int height, const int half_width)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, width * height);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            if (channel[i] < stif_lmean(channel, width, height, i, j, half_width))
                out[i] = 0;
            else
                out[i] = 1;
        }

    return out;
}

unsigned char*
threshold_percent(const unsigned char* const channel, const int size, const float percent)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, size);

    // TODO…

    return out;
}
