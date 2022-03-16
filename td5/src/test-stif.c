#include <imago2.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"
#include "img.h"
#include "stif.h"

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s IMAGE.\n"
        "    Compute and display statistical features.\n",
        s);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    if (argc != 2)
        usage(argv[0]);

    struct img_pixmap* img = img_load_image(argv[1]);
    unsigned char* channel = (unsigned char*)img->pixels;
    int width = img->width;
    int height = img->height;

    float mean = stif_mean(channel, width * height);
    int median = stif_median(channel, width * height);
    float standard_deviation = sqrt(stif_variance(channel, width * height));
    float entropy = stif_entropy(channel, width * height);

    printf("Mean: %d (%.3f).\n"
           "Median: %d (%.3f).\n"
           "Standard Deviation: %.1f (%.3f).\n"
           "Entropy: %.1f.\n",
        (int)round(mean), mean / (HISTOGRAM_NLEV - 1),
        median, (float)median / (HISTOGRAM_NLEV - 1),
        standard_deviation, standard_deviation / (HISTOGRAM_NLEV - 1),
        entropy);

    img_free(img);
    return EXIT_SUCCESS;
}
