#include "hysteresis.h"

#include <stdbool.h>
#include <stdlib.h>

#define MAX_IT 100

static bool
is_related(unsigned char* channel, int i, int j, int width, int height)
{
    for (int l = i - 1; l <= i + 1; l++) {
        if (l < 0 || l >= height)
            continue;

        for (int c = j - 1; c <= j + 1; c++) {
            if (c < 0 || c >= width)
                continue;

            if (channel[l * width + c] != 0)
                return true;
        }
    }

    return false;
}

unsigned char*
hysteresis_thr(unsigned char* channel, int width, int height, int th_low, int th_high)
{
    unsigned char* c = (unsigned char*)malloc(sizeof(unsigned char) * width * height);
    for (int i = 0; i < width * height; i++)
        c[i] = channel[i] >= th_high ? 255 : 0;

    bool convergence = false;
    int cpt = 0;
    while (!convergence) {
        for (int i = 0; i < height; i++)
            for (int j = 0; j < width; j++)
                if (th_high >= channel[i * width + j] && channel[i * width + j] >= th_low && is_related(c, i, j, width, height))
                    c[i * width + j] = 255;
        convergence = ++cpt == MAX_IT;
    }

    return c;
}
