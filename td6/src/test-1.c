#include <imago2.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "channel.h"
#include "convol1d.h"
#include "img.h"

static void
usage(char* s)
{
    fprintf(stderr,
        "Usage: %s -{h|v} -{t|n|a} [-i] INPUT OUTPUT\n"
        "    Apply a 1-D convolution of kernel [-1 1].\n"
        "    -h|-v : convolution direction (horizontal or vertical)\n"
        "    -t|-n|-a : display mode (truncation, normalization, absolute value\n"
        "    -i : inversion of output image\n",
        s);
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[])
{
    if (argc < 5)
        usage(argv[0]);

    int iarg = 1;

    enum conv_mode { Horizontal,
        Vertical };
    enum conv_mode conv_mode;

    if (strcmp(argv[iarg], "-h") == 0)
        conv_mode = Horizontal;
    else if (strcmp(argv[iarg], "-v") == 0)
        conv_mode = Vertical;
    else
        usage(argv[0]);
    iarg++;

    enum channel_disp_mode disp_mode;

    if (strcmp(argv[iarg], "-t") == 0)
        disp_mode = Cdm_truncate;
    else if (strcmp(argv[iarg], "-n") == 0)
        disp_mode = Cdm_normalize;
    else if (strcmp(argv[iarg], "-a") == 0)
        disp_mode = Cdm_absval;
    else
        usage(argv[0]);
    iarg++;

    bool invert_output = false;

    if (strcmp(argv[iarg], "-i") == 0) {
        invert_output = true;
        iarg++;
    }

    if (argc - iarg != 2)
        usage(argv[0]);

    char* input_file = argv[iarg];
    char* output_file = argv[iarg + 1];

    struct img_pixmap* img = img_load_gl_image(input_file);
    unsigned char* channel = (unsigned char*)img->pixels;
    int width = img->width;
    int height = img->height;

    float* f_channel = channel_to_float(channel, width * height);
    float* f_result = NULL;

    float kernel[3] = { 0.0, -1.0, 1.0 };

    switch (conv_mode) {
    case Horizontal:
        f_result = convol1d_apply_3(f_channel, width, height, kernel);
        break;

    case Vertical: {
        float* ch_1 = convol1d_swap_ij(f_channel, width, height);
        float* ch_2 = convol1d_apply_3(ch_1, height, width, kernel);
        f_result = convol1d_swap_ij(ch_2, height, width);
        free(ch_1);
        free(ch_2);
        break;
    }
    }

    unsigned char* result = channel_to_uchar(f_result, width * height, disp_mode);
    free(f_result);

    if (invert_output) {
        for (unsigned char* p = result + width * height - 1; p >= result; p--)
            *p = 255 - *p;
    }

    memcpy(channel, result, width * height * img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);

    exit(EXIT_SUCCESS);
}
