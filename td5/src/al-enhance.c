#include <imago2.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img.h"
#include "stif.h"

#define E 1e-2

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s HALF-WIDTH D IMAGE RESULT.\n"
        "    Build image resulting of contrast adaptative enhancement\n",
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
    int D = atoi(argv[2]);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            float lmean = stif_lmean(channel, width, height, i, j, half_width);
            float standard_deviation = sqrt(stif_lvariance(channel, width, height, i, j, half_width));
            channel[i * width + j] = lmean + D/(standard_deviation + E) * (channel[i * width + j] - lmean);
        }

    img_save(img, argv[4]);
    img_free(img);
    return EXIT_SUCCESS;
}
