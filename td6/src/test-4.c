#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <imago2.h>

#include "channel.h"
#include "convol1d.h"
#include "pderiv.h"
#include "img.h"
#include "gradient.h" 

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s -{2|3|p|s} [-i] INPUT OUTPUT\n"
	    "       %s -d ALPHA [-i] INPUT OUTPUT\n"

	    "    Compute gradient euclidean norm of INPUT.\n"
	    "    -2|3|p|s : kernel [-1 1], kernel [-1 0 1], prewitt, sobel\n"
	    "    -d : deriche derivative operator\n"
	    "    -i : inversion of output image\n"
	    , s, s);
    exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
    if (argc < 4)
	usage(argv[0]);
    
    int iarg = 1;
    
    enum deriv_mode { D2, D3, Prewitt, Sobel, Deriche };
    enum deriv_mode deriv_mode;
    float alpha = 0.0;
    
    if (strcmp(argv[iarg], "-2") == 0)
	deriv_mode = D2; 
    else if (strcmp(argv[iarg], "-3") == 0)
	deriv_mode = D3;
    else if (strcmp(argv[iarg], "-p") == 0)
	deriv_mode = Prewitt;
    else if (strcmp(argv[iarg], "-s") == 0)
	deriv_mode = Sobel;
    else if (strcmp(argv[iarg], "-d") == 0)
    {
	deriv_mode = Deriche;
	iarg++;
	alpha = atof(argv[iarg]);
    }
    else
	usage(argv[0]);
    iarg++;
    
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

    float *f_channel = channel_to_float(channel, width*height);

    float *di = NULL;
    float *dj = NULL;

    switch (deriv_mode)
    {
      case D2:
	di = pderiv_d2_di(f_channel, width, height);
	dj = pderiv_d2_dj(f_channel, width, height);
	break;

      case D3:
	di = pderiv_d3_di(f_channel, width, height);
	dj = pderiv_d3_dj(f_channel, width, height);
	break;

      case Prewitt:
	di = pderiv_prewitt_di(f_channel, width, height);
	dj = pderiv_prewitt_dj(f_channel, width, height);
	break;

      case Sobel:
	di = pderiv_sobel_di(f_channel, width, height);
	dj = pderiv_sobel_dj(f_channel, width, height);
	break;

      case Deriche:
	di = pderiv_deriche_di(f_channel, width, height, alpha);
	dj = pderiv_deriche_dj(f_channel, width, height, alpha);
	break;
    }

    float *f_result = gradient_norm_eucl(di, dj, width*height);
    free(di);
    free(dj);
    unsigned char *result = channel_to_uchar(f_result, width*height, Cdm_truncate);
    free(f_result);

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

