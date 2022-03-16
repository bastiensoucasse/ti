#include "convol1d.h"

#include <stdlib.h>

float*
convol1d_swap_ij(float* channel, int width, int height)
{
    float* c = (float*)malloc(sizeof(float) * width * height);
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            c[j * height + i] = channel[i * width + j];
    return c;
}

float*
convol1d_apply_3(float* channel, int width, int height, float kernel[3])
{
    float* c = (float*)malloc(sizeof(float) * width * height);
    for (int i = 0; i < height; i++) {
        c[i * width] = channel[i * width];
        c[i * width + width - 1] = channel[i * width + width - 1];
        for (int j = 1; j < width - 1; j++)
            c[i * width + j] = channel[i * width + j - 1] * kernel[2] + channel[i * width + j] * kernel[1] + channel[i * width + j + 1] * kernel[0];
    }
    return c;
}
