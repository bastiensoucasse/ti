#include "img.h"

#include <stdio.h>
#include <stdlib.h>

struct img_pixmap*
img_load_image(char* file_name)
{
    struct img_pixmap* img = img_create();

    if (img_load(img, file_name) == -1) {
        fprintf(stderr, "Could not load image \"%s\".\n", file_name);
        exit(EXIT_FAILURE);
    }
    if (img_is_float(img) || img_has_alpha(img) || !img_is_greyscale(img)) {
        fprintf(stderr, "Only greyscale 8 bits images.\n");
        exit(EXIT_FAILURE);
    }

    return img;
}
