#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>

int main(int argc, char **argv)
{
    if (argc != 3)
        fprintf(stderr, "Usage: img-convert INPUT_IMAGE OUTPUT_IMAGE\n"), exit(EXIT_FAILURE);

    struct img_pixmap *img = img_create();

    img_load(img, argv[1]);
    img_save(img, argv[2]);

    img_free(img);
    return EXIT_SUCCESS;
}
