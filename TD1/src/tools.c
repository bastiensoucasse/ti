#include "tools.h"

#include <stdio.h>
#include <stdlib.h>

#define NULLPXL 0

const unsigned char *channel_extract(const char *pixels, const size_t size, const unsigned int channel_number)
{
    unsigned char *mono = (unsigned char *)malloc(3 * size * sizeof(unsigned char));

    for (unsigned int i = 0; i < size; i++)
    {
        *(mono + 3 * i) = NULLPXL, *(mono + 3 * i + 1) = NULLPXL, *(mono + 3 * i + 2) = NULLPXL;
        *(mono + 3 * i + channel_number) = *(pixels + 3 * i + channel_number);
    }

    return mono;
}

const unsigned char *channel_compose(const char *r_chan, const char *g_chan, const char *b_chan, const size_t size)
{
    unsigned char *rgb = (unsigned char *)malloc(3 * size * sizeof(unsigned char));

    for (unsigned int i = 0; i < size; i++)
        *(rgb + 3 * i) = *(r_chan + 3 * i), *(rgb + 3 * i + 1) = *(g_chan + 3 * i + 1), *(rgb + 3 * i + 2) = *(b_chan + 3 * i + 2);

    return rgb;
}
