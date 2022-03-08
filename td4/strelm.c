#include "strelm.h"

#include <assert.h>
#include <float.h>
#include <imago2.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int i_min;
static int i_max;
static int j_min;
static int j_max;

static void
L_set_bbox(int width, int height, int ip, int jp, int radius)
{
    assert(radius >= 0);

    // i_min = ip - radius < 0 ? 0 : ip - radius;
    // i_max = ip + radius > height - 1 ? height - 1 : ip + radius;
    i_min = ip;
    i_max = ip;
    j_min = jp - radius < 0 ? 0 : jp - radius;
    j_max = jp + radius > width - 1 ? width - 1 : jp + radius;
}

// static bool
// L_is_inside_disk(int ip, int jp, int radius, int i, int j)
// {
//     const double dist = pow(i - ip, 2) + pow(j - jp, 2);
//     return dist <= pow(radius, 2);
// }

unsigned char
strelm_disk_getmin(unsigned char* channel, int width, int height, int ip, int jp, int radius)
{
    L_set_bbox(width, height, ip, jp, radius);

    unsigned char min = 255;
    for (int i = i_min; i <= i_max; i++)
        for (int j = j_min; j <= j_max; j++)
            min = /* L_is_inside_disk(ip, jp, radius, i, j) && */ channel[i * width + j] < min ? channel[i * width + j] : min;
    return min;
}

unsigned char
strelm_disk_getmax(unsigned char* channel, int width, int height, int ip, int jp, int radius)
{
    L_set_bbox(width, height, ip, jp, radius);

    unsigned char max = 0;
    for (int i = i_min; i <= i_max; i++)
        for (int j = j_min; j <= j_max; j++)
            max = /* L_is_inside_disk(ip, jp, radius, i, j) && */ channel[i * width + j] > max ? channel[i * width + j] : max;
    return max;
}
