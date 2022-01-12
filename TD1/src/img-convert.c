#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>


int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: img-convert INPUT_IMAGE OUTPUT_IMAGE\n");
        exit(EXIT_FAILURE);
    }

    struct img_pixmap *input = img_create();
    img_load(input, argv[1]);
    img_save(input, argv[2]);

    img_free(input);
    return EXIT_SUCCESS;
}
