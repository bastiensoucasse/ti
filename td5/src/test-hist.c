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
        "Usage: %s [-n] [-c] IMAGE.\n"
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

    int iargc = 1;
    while (iargc < argc) {
        if (strcmp(argv[iargc], "-c") == 0)
            cumulutated = true;
        else if (strcmp(argv[iargc], "-n") == 0)
            normalized = true;
        else if (argv[iargc][0] == '-')
            usage(argv[0]);
        else
            break;
        iargc++;
    }

    if (iargc != argc - 1)
        usage(argv[0]);

    struct img_pixmap* img = img_load_image(argv[iargc]);
    unsigned char* channel = (unsigned char*)img->pixels;
    int width = img->width;
    int height = img->height;

    float* histogram = histogram_make(channel, width * height);

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
