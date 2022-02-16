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

    L_DIFF_MISSINGCODE

    return result;
}

unsigned char*
mmip_disk_erosion(unsigned char* channel, int width, int height, int radius)
{
    unsigned char* result = malloc(width * height * sizeof(unsigned char));

    MMIP_DISK_EROSION_MISSINGCODE
}

unsigned char*
mmip_disk_dilatation(unsigned char* channel, int width, int height, int radius)
{
    MMIP_DISK_DILATATION_MISSINGCODE
}

unsigned char*
mmip_disk_opening(unsigned char* channel, int width, int height, int radius)
{
    MMIP_DISK_OPENING_MISSINGCODE
}

unsigned char*
mmip_disk_closing(unsigned char* channel, int width, int height, int radius)
{
    MMIP_DISK_CLOSING_MISSINGCODE
}

unsigned char*
mmip_disk_bgrad(unsigned char* channel, int width, int height, int radius)
{
    MMIP_DISK_BGRAD_MISSINGCODE
}

unsigned char*
mmip_disk_igrad(unsigned char* channel, int width, int height, int radius)
{
    MMIP_DISK_IGRAD_MISSINGCODE
}

unsigned char*
mmip_disk_ograd(unsigned char* channel, int width, int height, int radius)
{
    MMIP_DISK_OGRAD_MISSINGCODE
}
