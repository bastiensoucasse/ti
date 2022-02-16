#include "mmip.h"

#include <assert.h>
#include <float.h>
#include <imago2.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strelm.h"

#include "MISSING_CODE.h"

static unsigned char*
L_diff(unsigned char* i1, unsigned char* i2, int size)
{
    unsigned char* result = malloc(size * sizeof(unsigned char));

    for (int i = 0; i < size; i++)
        result[i] = i1[i] - i2[i];

    return result;
}

unsigned char*
mmip_disk_erosion(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* result = malloc(width * height * sizeof(unsigned char));

    for (int ip = 0; ip < height; ip++)
        for (int jp = 0; jp < width; jp++)
            result[ip * width + jp] = strelm_disk_getmin(channel, width, height, ip, jp, radius);

    return result;
}

unsigned char*
mmip_disk_dilatation(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* result = malloc(width * height * sizeof(unsigned char));

    for (int ip = 0; ip < height; ip++)
        for (int jp = 0; jp < width; jp++)
            result[ip * width + jp] = strelm_disk_getmax(channel, width, height, ip, jp, radius);

    return result;
}

unsigned char*
mmip_disk_opening(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* e = mmip_disk_erosion(channel, width, height, radius);
    unsigned char* d = mmip_disk_dilatation(e, width, height, radius);
    free(e);
    return d;
}

unsigned char*
mmip_disk_closing(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* d = mmip_disk_dilatation(channel, width, height, radius);
    unsigned char* e = mmip_disk_erosion(d, width, height, radius);
    free(d);
    return e;
}

unsigned char*
mmip_disk_bgrad(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* d = mmip_disk_dilatation(channel, width, height, radius);
    unsigned char* e = mmip_disk_erosion(channel, width, height, radius);
    unsigned char* result = L_diff(d, e, width * height);
    free(d), free(e);
    return result;
}

unsigned char*
mmip_disk_igrad(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* e = mmip_disk_erosion(channel, width, height, radius);
    unsigned char* result = L_diff(channel, e, width * height);
    free(e);
    return result;
}

unsigned char*
mmip_disk_ograd(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* d = mmip_disk_dilatation(channel, width, height, radius);
    unsigned char* result = L_diff(d, channel, width * height);
    free(d);
    return result;
}
