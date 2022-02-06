#ifndef FIP_H
#define FIP_H

#include <stdbool.h>

extern void
fip_save_image_spectrum(double* spectrum, int width, int height, char* name, bool phase);

extern void
fip_as_cut(double* spectrum, int width, int height, int min, int max, int mode);

extern void
fip_as_notch(double* spectrum, int width, int height, int u, int v, int r, float k);

#endif // FIP_H
