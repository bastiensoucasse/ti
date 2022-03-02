#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#include <imago2.h>

#include "histogram.h"
#include "stif.h"
#include "threshold.h"

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s THR IMAGE RESULT\n"
	    "Usage: %s [-m | -med ] IMAGE RESULT\n"
	    "Usage: %s -lm HALF-WIDTH IMAGE RESULT\n"
	    "Usage: %s -p PERCENT IMAGE RESULT\n"
	    "    Compute image thresholding relative to threshold THR\n"
	    "        -m : threshold is relative to image mean\n"
	    "        -med : threshold is relative to image median\n"
	    "        -lm : threshold is relative to local mean of half width HALF_WIDTH\n"
	    "        -p : threshold is relative P such that 10*P/N = PERCENT\n"
	    "             where N is the image number of pixels and 0 <= PERCENT <= 100)\n"
	    , s, s, s, s);
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
    enum Mode { Standard, Mean, Median, Lmean, Percent };
    enum Mode mode;
    int half_width;
    int percent;
    int threshold;
    int iargc = 1;

    if (argc == 1)
	usage(argv[0]);

    if (isdigit(argv[iargc][0]))
    {
	if (argc != 4)
	    usage(argv[0]);
	mode = Standard;
	threshold = atoi(argv[1]);
	iargc = 2;
    }
    else if (strcmp(argv[iargc], "-m") == 0)
    {
	if (argc != 4)
	    usage(argv[0]);
	mode = Mean;
	iargc = 2;
    }
    else if (strcmp(argv[iargc], "-med") == 0)
    {
	if (argc != 4)
	    usage(argv[0]);
	mode = Median;
	iargc = 2;
    }
    else if (strcmp(argv[iargc], "-lm") == 0)
    {
	if (argc != 5)
	    usage(argv[0]);
	mode = Lmean;
	half_width = atoi(argv[2]);
	iargc = 3;
	;
    }	
    else if (strcmp(argv[iargc], "-p") == 0)
    {
	if (argc != 5)
	    usage(argv[0]);
	mode = Percent;
	percent = atoi(argv[2]);
	if (percent < 0 || percent > 100)
	    usage(argv[0]);
	iargc = 3;
	;
    }
    else
	usage(argv[0]);
    
    struct img_pixmap *img = img_pixmap_read(argv[iargc]);
    char *output_file = argv[iargc + 1]; 

    unsigned char *channel = (unsigned char *) img->pixels;
    int width = img->width;
    int height = img->height;

    unsigned char *result = NULL;

    switch (mode)
    {
      case Standard:
	result = threshold_std(channel, width*height, threshold);
	break;

      case Mean:
	result = threshold_mean(channel, width*height);
	break;

      case Median:
	result = threshold_median(channel, width*height);
	break;

      case Lmean:
	result = threshold_lmean(channel, width, height, half_width);
	break;

      case Percent:
	result = threshold_percent(channel, width*height, percent);
	break;
    }

    memcpy(channel, result, width*height*img->pixelsz);
    img_save(img, output_file);

    img_free(img);
    
    exit(EXIT_SUCCESS);
}
