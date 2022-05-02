#ifndef FIP_H
#define FIP_H

#include <stdbool.h>

extern double*
fip_get_spectrum_from_pixels(const unsigned char* const pixels, const int width, const int height, const bool phase);

extern unsigned char*
fip_get_pixels_from_spectrum(const double* const spectrum, const int width, const int height, const bool phase);

extern void
fip_save_img_spectrum(const double* const spectrum, const int width, const int height, const char* const name, const bool phase);

#endif // FIP_H
