#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: img-format INPUT_IMAGE...\n");
        exit(EXIT_FAILURE);
    }

    struct img_pixmap *img = img_create();

    for (int i = 1; i < argc; i++)
    {
        const char *fname = (char *)argv[i];

        if (img_load(img, fname) == -1)
        {
            fprintf(stderr, "img-format: cannot load \"%s\"\n", fname);
            continue;
        }

        const int nbits = img_is_float(img) ? 16 : 8;

        if (img_is_greyscale(img))
        {
            printf("\"%s\": grayscale %d bits image\n", fname, nbits);
            continue;
        }

        const char* alpha = img_has_alpha(img) ? "with alpha channel" : "without alpha channel";

        printf("\"%s\": RGB %d bits image %s\n", fname, nbits, alpha);
    }

    img_free(img);
    return EXIT_SUCCESS;
}
