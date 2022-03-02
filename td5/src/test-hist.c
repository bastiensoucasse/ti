#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <imago2.h>

#include "histogram.h"
#include "stif.h"

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s [-c] [-n] IMAGE\n"
	    "    Compute and display standard histogram of IMAGE\n"
	    "        -c : compute cumulate histogram\n"
	    "        -n : compute normalized histogram\n"
	    "        both : compute normalized cumulate histogram\n"
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


int 
main(int argc, char *argv[])
{
    bool normalized = false;
    bool cumulutated = false;

    int iargc = 1;
    while (iargc < argc)
    {
	if (strcmp(argv[iargc], "-c") == 0)
	    cumulutated = true;
	else if (strcmp(argv[iargc], "-n") == 0)
	    normalized = true;
	else if (argv[iargc][0] == '-')
	    usage(argv[0]);
	else
	    break;
	iargc++;
    }
    
    if (iargc != argc - 1)
	usage(argv[0]);

    struct img_pixmap *img = img_pixmap_read(argv[iargc]);
    unsigned char *channel = (unsigned char *) img->pixels;
    int width = img->width;
    int height = img->height;

    float *h = histogram_make(channel, width*height);

    if (normalized)
	histogram_normalize(h);

    if (cumulutated)
	histogram_cumulate(h);

    for (int i = 0; i < 255; i++)
	printf("%f\n", h[i]);

    free(h);
    img_free(img);
    
    exit(EXIT_SUCCESS);
}
