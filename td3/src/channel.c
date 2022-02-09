#include "channel.h"

#define NULLPXL 0

unsigned char*
channel_extract(unsigned char* pixels, int size, int channel_number)
{
    unsigned char* mono = (unsigned char*)malloc(size * sizeof(unsigned char));

    for (unsigned int i = 0; i < size; i++)
        mono[i] = pixels[3 * i + channel_number];

    return mono;
}

unsigned char*
channel_compose(unsigned char* r_chan, unsigned char* g_chan, unsigned char* b_chan, size_t size)
{
    unsigned char* rgb = (unsigned char*)malloc(3 * size * sizeof(unsigned char));

    for (unsigned int i = 0; i < size; i++) {
        rgb[3 * i + 0] = r_chan[i];
        rgb[3 * i + 1] = g_chan[i];
        rgb[3 * i + 2] = b_chan[i];
    }

    return rgb;
}

unsigned char*
channel_dup(unsigned char* pixels, int size)
{
    unsigned char* dup = (unsigned char*)malloc(3 * size * sizeof(unsigned char));

    for (unsigned int i = 0; i < size; i++)
        dup[i] = pixels[i];

    return dup;
}
