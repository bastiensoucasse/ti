#include "tools.h"

#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>

int main(const int argc, const char **argv)
{
    if (argc != 5)
        fprintf(stderr, "Usage: img-comp RCHAN_INPUT GCHAN_INPUT BCHAN_INPUT OUTPUT_IMAGE\n"), exit(EXIT_FAILURE);

    struct img_pixmap *input_r = img_create(), *input_g = img_create(), *input_b = img_create(), *output = img_create();
    img_load(input_r, argv[1]), img_load(input_g, argv[2]), img_load(input_b, argv[3]);

    const unsigned char *pixels = channel_compose(input_r->pixels, input_g->pixels, input_b->pixels, input_r->width * input_r->height);

    if (img_set_pixels(output, input_r->width, input_r->height, input_r->fmt, (void *)pixels) == -1)
        exit(EXIT_FAILURE);

    img_save(output, argv[4]);
    free(pixels);

    img_free(input_r), img_free(input_g), img_free(input_b), img_free(output);
    return EXIT_SUCCESS;
}
