#include <stdlib.h>

#include <imago2.h>

#include "img.h"

struct img_pixmap *
img_load_gl_image(char *file_name)
{
    struct img_pixmap *img = img_create();

    if (img_load(img, file_name) == -1)
    {
	fprintf(stderr, "Cannot load \"%s\" image\n", file_name);
	exit(EXIT_FAILURE);
    }
    if (img_is_float(img) || !img_is_greyscale(img))
    {
	fprintf(stderr, "Sorry, only grey levels 8 bits images\n");
	exit(EXIT_FAILURE);
    }

    return img;
}


