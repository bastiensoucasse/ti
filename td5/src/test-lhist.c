#include <imago2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "histogram.h"
#include "img.h"

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s [-n] [-c] I J HALF-WIDTH IMAGE.\n"
        "    Compute and display standard histogram of IMAGE.\n"
        "        -n: Compute normalized histogram.\n"
        "        -c: Compute cumulate histogram.\n",
        s);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    bool normalized = false;
    bool cumulutated = false;

    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-c") == 0)
            cumulutated = true;
        else if (strcmp(argv[i], "-n") == 0)
            normalized = true;
        else if (argv[i][0] == '-')
            usage(argv[0]);

    if (argc < 5 || argc > 7)
        usage(argv[0]);

    struct img_pixmap* img = img_load_image(argv[argc - 1]);
    unsigned char* channel = (unsigned char*)img->pixels;
    int width = img->width;
    int height = img->height;

    int i = atoi(argv[argc - 4]);
    int j = atoi(argv[argc - 3]);
    int half_width = atoi(argv[argc - 2]);

    float* histogram = histogram_make_local(channel, width, height, i, j, half_width);

    if (normalized)
        histogram_normalize(histogram);

    if (cumulutated)
        histogram_cumulate(histogram);

    for (int i = 0; i < HISTOGRAM_NLEV; i++)
        printf("%f\n", histogram[i]);

    free(histogram);
    img_free(img);
    return EXIT_SUCCESS;
}
