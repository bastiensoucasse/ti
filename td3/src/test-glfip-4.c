#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <complex.h>
#include <fftw3.h>
#include <imago2.h>

#include "fft.h"
#include "fip.h"

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s INPUT OUTPUT MIN MAX MODE\n"
        "          If MODE = 0, cut frequencies lower than MIN and greater than MAX\n"
        "          If MODE = 1, cut frequencies in [MIN, MAX]\n",
        s);
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
process_channel(unsigned char* channel, int width, int height, int min, int max, int mode)
{
    fftw_complex* fr_channel = fft_forward(channel, width, height);
    double* as = fft_extract_as(fr_channel, width, height);
    double* ps = fft_extract_ps(fr_channel, width, height);

    fip_as_cut(as, width, height, min, max, mode);

    fftw_complex* fr_result = fft_compose_aps(as, ps, width, height);
    unsigned char* result = fft_backward(fr_result, width, height);

    fftw_free(fr_channel);
    free(as);
    free(ps);
    fftw_free(fr_result);

    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 6)
        usage(argv[0]);

    char* input_file = argv[1];
    char* output_file = argv[2];
    int min = atoi(argv[3]);
    int max = atoi(argv[4]);
    int mode = atoi(argv[5]);

    struct img_pixmap* img = img_pixmap_read(input_file);
    int width = img->width;
    int height = img->height;

    unsigned char* result = process_channel((unsigned char*)img->pixels, width, height,
        min, max, mode);

    memcpy(img->pixels, result, width * height * img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);

    exit(EXIT_SUCCESS);
}
