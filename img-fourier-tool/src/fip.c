#include "fip.h"

#include <math.h>
#include <stdlib.h>

#include "img-pixmap.h"

double*
fip_get_spectrum_from_pixels(const unsigned char* const pixels, const int width, const int height, const bool phase)
{
    double* const spectrum = (double*)malloc(width * height * sizeof(double));
    
    int max = pixels[0];
    for (unsigned int i = 1; i < width * height; i++)
        if (max < pixels[i])
            max = pixels[i];
    max *= 255;
    
    for (unsigned int i = 0; i < width * height; i++)
        spectrum[i] = max * pow(pixels[i] / 255., 1. / .15);
    
    if (phase)
        for (unsigned int i = 0; i < width * height; i++)
            spectrum[i] = spectrum[i] + 1. / 2.;

    return spectrum;
}

unsigned char*
fip_get_pixels_from_spectrum(const double* const spectrum, const int width, const int height, const bool phase)
{
    unsigned char* const pixels = (unsigned char*)malloc(width * height * sizeof(unsigned char));

    double max = spectrum[0];
    for (unsigned int i = 1; i < width * height; i++)
        if (max < spectrum[i])
            max = spectrum[i];

    double tmp[width * height];
    for (unsigned int i = 0; i < width * height; i++) {
        if (phase)
            tmp[i] = 255 * pow(((spectrum[i] / max) + 1) / 2, .15);
        else
            tmp[i] = 255 * pow(spectrum[i] / max, .15);

        if (tmp[i] < 0)
            tmp[i] = 0;
        if (tmp[i] > 255)
            tmp[i] = 255;
    }

    for (unsigned int i = 0; i < width * height; i++)
        pixels[i] = (unsigned char)tmp[i];

    return pixels;
}

void fip_save_img_spectrum(const double* const spectrum, const int width, const int height, const char* const path, const bool phase)
{
    unsigned char* const pixels = fip_get_pixels_from_spectrum(spectrum, width, height, phase);
    img_pixmap_save(pixels, width, height, path);
    free(pixels);
}
