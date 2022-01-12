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
            fprintf(stderr, "img-format: cannot load \"%s\"", fname);
            continue;
        }

        char *type;
        int bits;
        char *alpha;

        // if (img_is_float(img))
        //     printf("\"%s\": %s,");
    }

    img_free(img);
    return EXIT_SUCCESS;
}
