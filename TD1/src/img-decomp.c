#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>

int main(const int argc, const char **argv)
{
    if (argc != 5)
        fprintf(stderr, "Usage: img-decomp INPUT_IMAGE RCHAN_OUTPUT GCHAN_OUTPUT BCHAN_OUTPUT\n"), exit(EXIT_FAILURE);

    struct img_pixmap *input = img_create(), *output = img_create();
    img_load(input, argv[1]);

    for (unsigned int channel = 0; channel < 3; channel++)
    {
        const unsigned char *pixels = channel_extract(input->pixels, input->width * input->height, channel);

        if (img_set_pixels(output, input->width, input->height, input->fmt, (void *)pixels) == -1)
            exit(EXIT_FAILURE);

        img_save(output, argv[channel + 2]);
        free(pixels);
    }

    img_free(input), img_free(output);
    return EXIT_SUCCESS;
}
