#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>

#include <imago2.h>

#include "strelm.h"

#include "MISSING_CODE.h"
//#include "SOLUTION.h"

/* Bounding box */
static int i_min;
static int i_max;
static int j_min;
static int j_max;

static void
L_set_bbox(int width, int height, int ip, int jp, int radius)
{
    assert(radius >= 0);

    L_SET_BBOX_MISSINGCODE

}

static bool
L_is_inside_disk(int ip, int jp, int radius, int i, int j)
{
   L_IS_INSIDE_DISK_MISSINGCODE
}

unsigned char
strelm_disk_getmin(unsigned char *channel, int width, int height, int ip, int jp, int radius)
{
    L_set_bbox(width, height, ip, jp, radius);

    STRELM_DISK_GETMIN_MISSINGCODE
}

unsigned char
strelm_disk_getmax(unsigned char *channel, int width, int height, int ip, int jp, int radius)
{
    L_set_bbox(width, height, ip, jp, radius);

    STRELM_DISK_GETMAX_MISSINGCODE
}

    
