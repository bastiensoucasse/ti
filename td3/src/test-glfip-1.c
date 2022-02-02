#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <complex.h>
#include <fftw3.h>
#include <imago2.h>

#include "fft.h"

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s [-z] INPUT OUTPUT\n", s);
    exit(EXIT_FAILURE);
}

static struct img_pixmap*
img_pixmap_read(char* file_name)
{
    struct img_pixmap* img = img_create();

    if (img_load(img, file_name) == -1) {
        fprintf(stderr, "Cannot load \"%s\" image\n", file_name);
        exit(EXIT_FAILURE);
    }
    if (img_is_float(img) || img_has_alpha(img) || !img_is_greyscale(img)) {
        fprintf(stderr, "Sorry, only grey levels 8 bits images\n");
        exit(EXIT_FAILURE);
    }

    return img;
}

static unsigned char*
process_channel(unsigned char* channel, int width, int height, bool clear_zero)
{
    fftw_complex* fr_channel = fft_forward(channel, width, height);

    if (clear_zero) {
        int i = height / 2;
        int j = width / 2;

        fr_channel[(i - 1) * width + j - 1] = 0.0;
        fr_channel[(i - 1) * width + j] = 0.0;
        fr_channel[(i - 1) * width + j + 1] = 0.0;

        fr_channel[i * width + j - 1] = 0.0;
        fr_channel[i * width + j] = 0.0;
        fr_channel[i * width + j + 1] = 0.0;

        fr_channel[(i + 1) * width + j - 1] = 0.0;
        fr_channel[(i + 1) * width + j] = 0.0;
        fr_channel[(i + 1) * width + j + 11] = 0.0;
    }

    unsigned char* result = fft_backward(fr_channel, width, height);

    fftw_free(fr_channel);

    return result;
}

int main(int argc, char* argv[])
{
    bool clear_zero = false;
    char* input_file;
    char* output_file;

    if (argc == 3) {
        input_file = argv[1];
        output_file = argv[2];
    } else if (argc == 4) {
        if (strcmp(argv[1], "-z") == 0) {
            clear_zero = true;
            input_file = argv[2];
            output_file = argv[3];
        } else
            usage(argv[0]);
    } else
        usage(argv[0]);

    struct img_pixmap* img = img_pixmap_read(input_file);
    int width = img->width;
    int height = img->height;

    unsigned char* result = process_channel((unsigned char*)img->pixels, width, height, clear_zero);

    memcpy(img->pixels, result, width * height * img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);

    exit(EXIT_SUCCESS);
}
