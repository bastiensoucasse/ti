#include "channel.h"

#include <math.h>
#include <stdlib.h>

float*
channel_to_float(unsigned char* channel, int size)
{
    float* fchannel = (float*)malloc(sizeof(float) * size);
    for (int i = 0; i < size; i++)
        fchannel[i] = (float)channel[i];
    return fchannel;
}

unsigned char*
channel_to_uchar(float* fchannel, int size, enum channel_disp_mode mode)
{
    unsigned char* channel = (unsigned char*)malloc(sizeof(unsigned char) * size);
    for (int i = 0; i < size; i++)
        switch (mode) {
        case Cdm_normalize:
            channel[i] = 0.5 * fchannel[i] + 127;
            break;
        case Cdm_truncate:
            channel[i] = fchannel[i] < 0 ? 0 : fchannel[i];
            break;
        case Cdm_absval:
            channel[i] = fabsf(fchannel[i]);
            break;
        }
    return channel;
}