#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <imago2.h>

#include "channel.h"
#include "convol1d.h"
#include "pderiv.h"
#include "img.h"

static void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s -{di|dj} -{2|3|p|s} -{t|n|a} [-i] INPUT OUTPUT\n"
	    "       %s -{di|dj} -d ALPHA -{t|n|a} [-i] INPUT OUTPUT\n"

	    "  Compute partial derivatives of INPUT.\n"
	    "    -di|-dh : partial derivation from i or j\n"
	    "    -2|3|p|s : kernel [-1 1], kernel [-1 0 1], prewitt, sobel\n"
	    "    -d : deriche derivative operator\n"
	    "    -t|-n|-a : display mode (truncation, normalization, absolute value\n"
	    "    -i : inversion of output image\n"
	    , s, s);
    exit(EXIT_FAILURE);
}

int 
main(int argc, char *argv[])
{
    if (argc < 6)
	usage(argv[0]);

    enum Pdivaxis { Di, Dj };
    enum Pdivaxis pdivaxis;

    if (strcmp(argv[1], "-di") == 0)
	pdivaxis = Di;
    else if (strcmp(argv[1], "-dj") == 0)
	pdivaxis = Dj;
    else
	usage(argv[0]);

    int iarg = 2;
    
    enum deriv_mode { D2, D3, Prewitt, Sobel, Deriche };
    enum deriv_mode deriv_mode;
    float alpha = 0.0;
        
     if (strcmp(argv[2], "-2") == 0)
	deriv_mode = D2; 
    else if (strcmp(argv[2], "-3") == 0)
	deriv_mode = D3;
    else if (strcmp(argv[2], "-p") == 0)
	deriv_mode = Prewitt;
    else if (strcmp(argv[2], "-s") == 0)
	deriv_mode = Sobel;
    else if (strcmp(argv[2], "-d") == 0)
    {
	deriv_mode = Deriche;
	iarg++;
	alpha = atof(argv[iarg]);
    }
    else
	usage(argv[0]);
     iarg++;
    
    enum channel_disp_mode disp_mode;

    if (strcmp(argv[iarg], "-t") == 0)
	disp_mode = Cdm_truncate; 
    else if (strcmp(argv[iarg], "-n") == 0)
	disp_mode = Cdm_normalize;
    else if (strcmp(argv[iarg], "-a") == 0)
	disp_mode = Cdm_absval;
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
    float *f_result = NULL;

    switch (deriv_mode)
    {
      case D2:
	switch (pdivaxis)
	{
	  case Di:
	    f_result = pderiv_d2_di(f_channel, width, height);
	    break;

	  case Dj:
	    f_result = pderiv_d2_dj(f_channel, width, height);
	    break;
	}
	break;

      case D3:
	switch (pdivaxis)
	{
	  case Di:
	    f_result = pderiv_d3_di(f_channel, width, height);
	    break;

	  case Dj:
	    f_result = pderiv_d3_dj(f_channel, width, height);
	    break;
	}
	break;

      case Prewitt:
	switch (pdivaxis)
	{
	  case Di:
	    f_result = pderiv_prewitt_di(f_channel, width, height);
	    break;

	  case Dj:
	    f_result = pderiv_prewitt_dj(f_channel, width, height);
	    break;
	}
	break;

      case Sobel:
	switch (pdivaxis)
	{
	  case Di:
	    f_result = pderiv_sobel_di(f_channel, width, height);
	    break;

	  case Dj:
	    f_result = pderiv_sobel_dj(f_channel, width, height);
	    break;
	}
	break;

      case Deriche:
	switch (pdivaxis)
	{
	  case Di:
	    f_result = pderiv_deriche_di(f_channel, width, height, alpha);
	    break;

	  case Dj:
	    f_result = pderiv_deriche_dj(f_channel, width, height, alpha);
	    break;
	}
	break;
    }
    
    unsigned char *result = channel_to_uchar(f_result, width*height, disp_mode);
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
