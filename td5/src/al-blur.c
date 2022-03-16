#include <imago2.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img.h"
#include "stif.h"

static unsigned char*
channel_malloc(int size)
{
    unsigned char* channel = (unsigned char*)malloc(size * sizeof(unsigned char));
    if (!channel) {
        fprintf(stderr, "Not enough memory.\n");
        exit(EXIT_FAILURE);
    }
    return channel;
}

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s HALF-WIDTH T IMAGE RESULT.\n"
        "    Build image resulting of adaptative smoothing\n",
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
    unsigned char T = atoi(argv[2]);

    unsigned char* result = channel_malloc(width * height);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            float lmean = stif_lmean(channel, width, height, i, j, half_width);
            result[i * width + j] = fabsf(channel[i * width + j] - lmean) <= T ? (unsigned char)round(lmean) : channel[i * width + j];
        }

    memcpy((void*)channel, result, width * height * img->pixelsz);
    free(result);
    img_save(img, argv[4]);
    img_free(img);
    return EXIT_SUCCESS;
}
