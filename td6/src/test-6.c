#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>

#include <imago2.h>

#include "img.h"
#include "threshold.h"
#include "hysteresis.h"

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s THR [-i] IMAGE RESULT\n"
	    "       %s -m [-i] IMAGE RESULT\n"
	    "       %s -p [-i] PERCENT IMAGE RESULT\n\n"
	    "       %s -h LOW HIGH [-i] IMAGE RESULT\n\n"
	    
	    "    Compute image thresholding relative to threshold THR\n"
	    "    -m : threshold is relative to image mean\n"
	    "    -p : threshold is relative P such that 10*P/N = PERCENT\n"
	    "         where N is the image number of pixels and 0 <= PERCENT <= 100)\n"
	    "    -h : hysteresis thresholding with respect to thresholds HIGH and LOW\n"
	    "    -i : inversion of output image\n"
	    , s, s, s, s);
    exit(EXIT_FAILURE);
}


int 
main(int argc, char *argv[])
{
    enum Mode { Standard, Mean, Percent, Hysteresis };
    enum Mode mode;
    
    int percent;
    int threshold;
    int th_high;
    int th_low;
    
    if (argc == 1)
	usage(argv[0]);

    int iarg = 1;

    if (isdigit(argv[iarg][0]))
    {
	if (argc < 4)
	    usage(argv[0]);
	mode = Standard;
	threshold = atoi(argv[1]);
	iarg = 2;
    }
    else if (argv[iarg][0] != '-')
	usage(argv[0]);
    else
	switch (argv[iarg][1])
	{
	  case 'm':
	    if (argc < 4)
		usage(argv[0]);
	    mode = Mean;
	    iarg = 2;
	    break;

	  case 'p':
	    if (argc < 5)
		usage(argv[0]);
	    mode = Percent;
	    percent = atoi(argv[2]);
	    if (percent < 0 || percent > 100)
		usage(argv[0]);
	    iarg = 3;
	    break;

	  case 'h':
	    if (argc < 6)
		usage(argv[0]);
	    mode = Hysteresis;
	    th_low = atoi(argv[iarg + 1]);
	    th_high = atoi(argv[iarg + 2]);
	    iarg = 4;
	    break;

	  case 'i':
	    break;

	  default:
	    usage(argv[0]);
	}

    bool invert_output = false;
    
    if (strcmp(argv[iarg], "-i") == 0)
    {
	invert_output = true;
	iarg++;
    }
    
    if (argc - iarg != 2)
	usage(argv[0]); 
    char *input_file = argv[iarg];
    char *output_file = argv[iarg + 1]; 

    struct img_pixmap *img = img_load_gl_image(input_file);
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

      case Percent:
	result = threshold_percent(channel, width*height, percent);
	break;

      case Hysteresis:
	result = hysteresis_thr(channel, width, height, th_low, th_high);
	break;
    }

    if (invert_output)
    {
	for (unsigned char *p = result + width*height - 1; p >= result; p--)
	    *p = 255 - *p;
    }
 
    memcpy(channel, result, width*height*img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);
    
    exit(EXIT_SUCCESS);
}
