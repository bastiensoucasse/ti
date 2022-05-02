#include "img-pixmap.h"

#include <stdlib.h>

struct img_pixmap*
img_pixmap_read(const char* const path)
{
    struct img_pixmap* const img = img_create();

    if (img_load(img, path) == -1) {
        fprintf(stderr, "Cannot load \"%s\" image.\n", path);
        exit(EXIT_FAILURE);
    }

    if (img_is_float(img) || img_has_alpha(img) || !img_is_greyscale(img)) {
        fprintf(stderr, "Only grey levels 8 bits images accepted.\n");
        exit(EXIT_FAILURE);
    }

    return img;
}

void img_pixmap_save(unsigned char* const pixels, const int width, const int height, const char* const path)
{
    struct img_pixmap* const img = img_create();

    img_set_pixels(img, width, height, IMG_FMT_GREY8, pixels);
    img_save(img, path);

    img_destroy(img);
}
