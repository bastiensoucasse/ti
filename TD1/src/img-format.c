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
        if (img_load(img, argv[i]) == -1)
        {
            fprintf("img-format: cannot load \"%s\"", argv[i]);
            continue;
        }
        
        char *type;
        int bits;
        char *alpha;

        if (img_is_float(img))
            printf("\"%s\": %s,")
        
    }

    return EXIT_SUCCESS;
}