#include "tools.h"

#include <stdio.h>
#include <stdlib.h>

#define NULLPXL 0

const char *channel_extract(const char *pixels, const size_t size, const unsigned int channel_number)
{
    char *mono = (char *)malloc(3 * size * sizeof(char));

    for (unsigned int i = 0; i < size; i++)
    {
        *(mono + 3 * i) = NULLPXL, *(mono + 3 * i + 1) = NULLPXL, *(mono + 3 * i + 2) = NULLPXL;
        *(mono + 3 * i + channel_number) = *(pixels + 3 * i + channel_number);
    }

    return mono;
}

const char *channel_compose(const char *r_chan, const char *g_chan, const char *b_chan, const size_t size)
{
    char *rgb = (char *)malloc(3 * size * sizeof(char));

    for (unsigned int i = 0; i < size; i++)
        *(rgb + 3 * i) = *(r_chan + 3 * i), *(rgb + 3 * i + 1) = *(g_chan + 3 * i + 1), *(rgb + 3 * i + 2) = *(b_chan + 3 * i + 2);

    return rgb;
}

/*
///
/// WARNING: To be deleted, debug testing only.
///
int main(const int argc, const char **argv)
{
    const char *pixels = "123123123123";
    printf("[DEBUG] pixels = %s\n", pixels);

    const char *r_chan = channel_extract(pixels, 4, 0);
    printf("[DEBUG] r_chan = %s\n", r_chan);

    const char *g_chan = channel_extract(pixels, 4, 1);
    printf("[DEBUG] g_chan = %s\n", g_chan);

    const char *b_chan = channel_extract(pixels, 4, 2);
    printf("[DEBUG] b_chan = %s\n", b_chan);

    const char *rgb = channel_compose(r_chan, g_chan, b_chan, 4);
    printf("[DEBUG] rgb = %s\n", rgb);

    return EXIT_SUCCESS;
}
*/
