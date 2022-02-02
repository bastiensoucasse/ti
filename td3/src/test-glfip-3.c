#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <complex.h>
#include <fftw3.h>
#include <imago2.h>

#include "fip.h"
#include "fft.h"

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s INPUT OUTPUT AS_NAME PS_NAME\n"
	    , s);
    exit(EXIT_FAILURE);
}

static struct img_pixmap *
img_pixmap_read(char *file_name)
{
    struct img_pixmap *img = img_create();

    if (img_load(img, file_name) == -1)
    {
	fprintf(stderr, "Cannot load \"%s\" image\n", file_name);
	exit(EXIT_FAILURE);
    }
    if (img_is_float(img) || img_has_alpha(img) || !img_is_greyscale(img))
    {
	fprintf(stderr, "Sorry, only grey levels 8 bits images\n");
	exit(EXIT_FAILURE);
    }

    return img;
}




static unsigned char *
process_channel(unsigned char *channel, int width, int height, char *as_name, char *ps_name)
{
    fftw_complex *fr_channel = fft_forward(channel, width, height);
    double *as = fft_extract_as(fr_channel, width, height);
    double *ps = fft_extract_ps(fr_channel, width, height);

    fip_save_image_spectrum(as, width, height, as_name, false);
    fip_save_image_spectrum(ps, width, height, ps_name, true);
    
    fftw_complex *fr_result = fft_compose_aps(as, ps, width, height);
    unsigned char *result = fft_backward(fr_result, width, height);

    fftw_free(fr_channel); 
    free(as);
    free(ps);
    fftw_free(fr_result);

    return result;    
}

int 
main(int argc, char *argv[])
{
    if (argc != 5)
	usage(argv[0]);

    char *input_file = argv[1];
    char *output_file = argv[2];
    char *output_as_file = argv[3];
    char *output_ps_file = argv[4];

    struct img_pixmap *img = img_pixmap_read(input_file);
    int width = img->width;
    int height = img->height;

    unsigned char *result = process_channel((unsigned char *) img->pixels, width, height,
					    output_as_file, output_ps_file);

    memcpy(img->pixels, result, width*height*img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);

    exit(EXIT_SUCCESS);
}

