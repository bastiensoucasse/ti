#include <imago2.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "histogram.h"
#include "img.h"
#include "stif.h"

static void
usage(const char* const s)
{
    fprintf(stderr,
        "Usage: %s IMAGE.\n"
        "    Compute and display statistical features.\n",
        s);
    exit(EXIT_FAILURE);
}

int main(const int argc, const char* const* const argv)
{
    if (argc != 2)
        usage(argv[0]);

    struct img_pixmap* img = img_load_image(argv[1]);
    const unsigned char* channel = (unsigned char*)img->pixels;
    const int width = img->width;
    const int height = img->height;

    const float mean = stif_mean(channel, width * height);
    const int median = stif_median(channel, width * height);
    const float standard_deviation = sqrt(stif_variance(channel, width * height));
    const float entropy = stif_entropy(channel, width * height);

    printf("Mean: %5.1f (%5.3f).\n"
           "Median: %5d (%5.3f).\n"
           "Standard Deviation: %5.1f (%5.3f).\n"
           "Entropy: %5.1f.\n",
        mean, mean / (HISTOGRAM_NLEV - 1),
        median, (float)median / (HISTOGRAM_NLEV - 1),
        standard_deviation, standard_deviation / (HISTOGRAM_NLEV - 1),
        entropy);

    img_free(img);

    return EXIT_SUCCESS;
}
