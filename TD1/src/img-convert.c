#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>


// void img_convert(struct img_pixmap *input, struct img_pixmap *output)
// {
//     int h = input->height;
//     int w = input->width;

//     for (int i = 0; i < h; i++)

//     img_free(img);
// }


int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: img-convert INPUT_IMAGE OUTPUT_IMAGE\n");
        exit(EXIT_FAILURE);
    }

    struct img_pixmap *input = img_create();
    img_load(input, argv[1]);

    struct img_pixmap *output = img_create();

    printf("Input: width = %d, height = %d, fmt = %d, name = %s\n", input->width, input->height, input->fmt, input->name);

    // img_convert(input, output);

    return EXIT_SUCCESS;
}
