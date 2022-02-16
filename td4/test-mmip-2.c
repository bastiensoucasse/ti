#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <complex.h>
#include <fftw3.h>
#include <imago2.h>

#include "mmip.h"
// #include "misc.h"

static void
usage(char *s)
{
    fprintf(stderr, "Usage: %s [-i|-e] RADIUS INPUT OUTPUT\n" , s);
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

int 
main(int argc, char *argv[])
{
    enum mode { Beucher, Internal, External };
    
    if (argc < 4)
	usage(argv[0]);
    
    int iargc = 1;
    enum mode mode = Beucher;

    if (strcmp(argv[iargc], "-i") == 0)
    {
	iargc++;
	mode = Internal;
    }
    else if (strcmp(argv[iargc], "-e") == 0)
    {
	iargc++;
	mode = External;
    }
    else if (argv[iargc][0] == '-')
    {
	fprintf(stderr, "%s: unknowm otion (must be -b, -i, -e)", argv[iargc]);
	usage(argv[0]);
    }
    if (argc - iargc != 3)
	usage(argv[0]);
    
    int radius = atoi(argv[iargc]);
    char *input_file = argv[iargc + 1];
    char *output_file = argv[iargc + 2];
    
    struct img_pixmap *img = img_pixmap_read(input_file);
    unsigned char *img_buffer = (unsigned char *) img->pixels;
    int width = img->width;
    int height = img->height;
    
    unsigned char *result = NULL;
    switch (mode)
    {
      case Beucher:
	result = mmip_disk_bgrad(img_buffer, width, height, radius);
	break;

      case Internal:
	result = mmip_disk_igrad(img_buffer, width, height, radius);
	break;

      case External:
	result = mmip_disk_ograd(img_buffer, width, height, radius);
    }

    memcpy(img_buffer, result, width*height*img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);

    exit(EXIT_SUCCESS);
}
