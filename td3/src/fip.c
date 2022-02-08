#include "fip.h"

#include <math.h>
#include <imago2.h>

void
fip_save_image_spectrum(double* spectrum, int width, int height, char* name, bool phase)
{
    struct img_pixmap* img = img_create();                                                            

    double max = spectrum[0];
    for (unsigned int i = 1; i < width * height; i++)
        if (max < spectrum[i])
            max = spectrum[i];

    for (unsigned int i = 0; i < width * height; i++)
        if (phase)
            spectrum[i] = 255 * pow(((spectrum[i] / max) + 1) / 2, .15);
        else
            spectrum[i] = 255 * pow(spectrum[i] / max, .15);
    
    img_set_pixels(img, width, height, IMG_FMT_GREY8, spectrum);
    img_save(img, name);
}

void
fip_as_cut(double* spectrum, int width, int height, int min, int max, int mode)
{
    // if (mode == 1)
    //     for (int i = min; i <= max; i++)
    //         spectrum[i] = 0;
    // else
    // {
    //     for (int i = 0; i < min; i++)
    //         spectrum[i] = 0;
    //     for (int i = max+1; i < width * height; i++)
    //         spectrum[i] = 0;
    // }

    for (int i = 0; i < width * height; i++)
    {
        if (mode == 1)
            spectrum[i] = min <= i && i <= max ? 0 : spectrum[i];
        else
            spectrum[i] = i < min || max < i ? 0 : spectrum[i];
    }
}
