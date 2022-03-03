#include "threshold.h"

#include <stdlib.h>
#include <string.h>

#include "histogram.h"
#include "stif.h"

unsigned char*
threshold_std(const unsigned char* const channel, const int size, const unsigned char th)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, size);

    float* const histogram = histogram_make(channel, size);
    histogram_normalize(histogram);
    histogram_cumulate(histogram);

    // …

    return out;
}

unsigned char*
threshold_mean(const unsigned char* const channel, const int size)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, size);

    return out;
}

unsigned char*
threshold_median(const unsigned char* const channel, const int size)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, size);

    return out;
}

unsigned char*
threshold_lmean(const unsigned char* const channel, const int width, const int height, const int half_width)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, width * height);

    return out;
}

unsigned char*
threshold_percent(const unsigned char* const channel, const int size, const float percent)
{
    unsigned char* const out = NULL;
    memcpy(out, channel, size);

    return out;
}
