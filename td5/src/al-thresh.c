#include <imago2.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img.h"
#include "stif.h"

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s HALF-WIDTH K IMAGE RESULT.\n"
        "    Build image resulting of adaptative thresholding\n",
        s);
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv)
{
    if (argc != 5)
        usage(argv[0]);

    struct img_pixmap* img = img_load_image(argv[3]);
    unsigned char* channel = (unsigned char*)img->pixels;
    int width = img->width;
    int height = img->height;

    int half_width = atoi(argv[1]);
    float K = atof(argv[2]);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            float standard_deviation = sqrt(stif_lvariance(channel, width, height, i, j, half_width));
            float T = stif_lmean(channel, width, height, i, j, half_width) - K * standard_deviation;
            channel[i * width + j] = channel[i * width + j] <= T ? 0 : 1;
        }

    img_save(img, argv[4]);
    img_free(img);
    return EXIT_SUCCESS;
}
