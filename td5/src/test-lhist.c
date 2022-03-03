#include <imago2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "histogram.h"
#include "img.h"

static void
usage(const char* const s)
{
    fprintf(stderr,
        "Usage: %s [-n] [-c] I J HALF-WIDTH IMAGE.\n"
        "    Compute and display standard histogram of IMAGE.\n"
        "        -n: Compute normalized histogram.\n"
        "        -c: Compute cumulate histogram.\n",
        s);
    exit(EXIT_FAILURE);
}

int main(const int argc, const char* const* const argv)
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
    const unsigned char* const channel = (unsigned char*)img->pixels;
    const int width = img->width;
    const int height = img->height;

    const int i = atoi(argv[iargc - 3]);
    const int j = atoi(argv[iargc - 2]);
    const int half_width = atoi(argv[iargc - 1]);

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
