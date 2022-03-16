#ifndef CHANNEL_H
#define CHANNEL_H

#include <stdbool.h>

enum channel_disp_mode {
    Cdm_normalize,
    Cdm_truncate,
    Cdm_absval
};

extern float*
channel_to_float(unsigned char* channel, int size);

extern unsigned char*
channel_to_uchar(float* fchannel, int size, enum channel_disp_mode mode);

#endif // CHANNEL_H
