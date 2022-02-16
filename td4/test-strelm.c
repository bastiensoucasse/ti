#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <complex.h>
#include <fftw3.h>
#include <imago2.h>

#include "strelm.h"

enum mode { Minimum, Maximum, Default };

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


static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s [-m | -M] I J R IMAGE\n\n"
	    "Computes minimum and/or maximum of gray level image IMAGE "
	    "according to a circular\nstructuring element of radius R\n\n"
	    "        -m : print minimum\n"
	    "        -M : print maximum\n"
	    "        without argument : print both together with coordinates"
	    " and radius arguments\n\n" 
	    , s);
    exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
    if (argc < 5)
	usage(argv[0]);

    int iargc = 1;
    enum mode mode = Default;
    
    if (strcmp(argv[iargc], "-M") == 0)
    {
	mode = Maximum;
	iargc++;
    }
    else if (strcmp(argv[iargc], "-m") == 0)
    {
	mode = Minimum;
	iargc++;
    }
    else if (argv[iargc][0] == '-')
	usage(argv[0]);
    
    if (argc - iargc != 4)
	usage(argv[0]);
	    
    int ip = atoi(argv[iargc]);
    int jp = atoi(argv[iargc + 1]);
    int radius = atoi(argv[iargc + 2]);
    char *input_file = argv[iargc + 3];

    struct img_pixmap *img = img_pixmap_read(input_file);
    int width = img->width;
    int height = img->height;

    switch (mode)
    {
      case Minimum:
	printf("%d\n", strelm_disk_getmin((unsigned char *) img->pixels,
					  width, height, ip, jp, radius));
	break;

      case Maximum:
	printf("%d\n", strelm_disk_getmax((unsigned char *) img->pixels,
					  width, height, ip, jp, radius));
	break;

      case Default:
      {
	  int v_min = strelm_disk_getmin((unsigned char *) img->pixels,
					 width, height, ip, jp, radius);
	  int v_max = strelm_disk_getmax((unsigned char *) img->pixels,
					 width, height, ip, jp, radius);
	  printf("p = (%d,%d) ; R = %d ; min = %d, max = %d\n",
		 ip, jp, radius, v_min, v_max);
      }
    }

    img_free(img);

    exit(EXIT_SUCCESS);
}
