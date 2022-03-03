#include "img.h"

#include <stdio.h>
#include <stdlib.h>

struct img_pixmap*
img_load_image(const char* const filename)
{
    struct img_pixmap* img = img_create();

    if (img_load(img, filename) == -1) {
        fprintf(stderr, "Could not load image \"%s\".\n", filename);
        exit(EXIT_FAILURE);
    }
    if (img_is_float(img) || img_has_alpha(img) || !img_is_greyscale(img)) {
        fprintf(stderr, "Only greyscale 8 bits images.\n");
        exit(EXIT_FAILURE);
    }

    return img;
}
