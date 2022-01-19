#include "tools.h"

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: img-decomp INPUT_IMAGE RCHAN_OUTPUT GCHAN_OUTPUT BCHAN_OUTPUT\n");
        exit(EXIT_FAILURE);
    }

    const char *input = argv[1];

    struct img_pixmap *img = img_create();
    img_load(img, );

    const char *r_chan = channel_extract(img->)

    img_free(img);

    return EXIT_SUCCESS;
}
