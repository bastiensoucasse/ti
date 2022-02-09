#include "fip.h"

#include <imago2.h>
#include <math.h>
#include <stdlib.h>

void fip_save_image_spectrum(double* spectrum, int width, int height, char* name, bool phase)
{
    double tmp[width * height];

    struct img_pixmap* img = img_create();
    unsigned char* pixels = (unsigned char*)malloc(width * height * sizeof(unsigned char));

    double max = spectrum[0];
    for (unsigned int i = 1; i < width * height; i++)
        if (max < spectrum[i])
            max = spectrum[i];

    for (unsigned int i = 0; i < width * height; i++) {
        if (phase)
            tmp[i] = 255 * pow(((spectrum[i] / max) + 1) / 2, .15);
        else
            tmp[i] = 255 * pow(spectrum[i] / max, .15);

        // Thresholding
        if (tmp[i] < 0)
            tmp[i] = 0;
        if (tmp[i] > 255)
            tmp[i] = 255;
    }
    
    for (unsigned int i = 0; i < width * height; i++)
        pixels[i] = (unsigned char) tmp[i];

    img_set_pixels(img, width, height, IMG_FMT_GREY8, pixels);
    img_save(img, name);
}

void fip_as_cut(double* spectrum, int width, int height, int min, int max, int mode)
{
    for (int i = 0; i < width * height; i++) {
        if (mode == 1)
            spectrum[i] = min <= spectrum[i] && spectrum[i] <= max ? 0. : spectrum[i];
        else
            spectrum[i] = spectrum[i] < min || max < spectrum[i] ? 0. : spectrum[i];
    }
}
