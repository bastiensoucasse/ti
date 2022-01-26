#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "sed.h"
#include "xyz.h"
#include "colorimetric_data.h"

#include "MISSINGCODE.h"

void
usage(char *s)
{
    fprintf(stderr,
	    "Usage: %s [-gmcc] -D65|-A|-n\n"
	    "Usage: %s [-gmcc] -K TEMP\n"
	    "    -D65|-A|-n : display sRGB coordinates of D65 standard illuminant\n"
	    "        A standard illuminant, or neutral source (E(lambda) = 1.0)\n"
	    "    -K : display sRGB coordinates of planckplanck blackbody for a\n"
	    "        temperature of TEMP degrees Kelvin\n"
	    "    -gmcc : display sRGB coordinates illuminated by the specified\n"
	    "        light source.\n"
	    , s, s);
        exit(EXIT_FAILURE);
}

static int
L_clamp(int v)
{
    if (v < 0)
	return 0;
    if (v > 255)
	return 255;
    return v;
}

static void
print_rgb_of_sed(float *e, float k)
{
    float xyz[3];

    xyz_from_sed(xyz, e, k);
    
    float r = xyz_srgb_r(xyz[0], xyz[1], xyz[2]);
    float g = xyz_srgb_g(xyz[0], xyz[1], xyz[2]);
    float b = xyz_srgb_b(xyz[0], xyz[1], xyz[2]);

    int ir = L_clamp((int)(r*255 + 0.5));
    int ig = L_clamp((int)(g*255 + 0.5));
    int ib = L_clamp((int)(b*255 + 0.5));

    printf("%3d %3d %3d\n", ir, ig, ib);
}

static void
print_gmcc_colors(float *light_source)
{

PRINT_GMCC_COLORS_MISSINGCODE    
 
}


int
main(int argc, char *argv[])
{
    int iarg = 1;

    if (iarg == argc)
	usage(argv[0]);

    bool gmcc_mode = false;
    if (strcmp(argv[iarg], "-gmcc") == 0)
    {
	gmcc_mode = true;
	iarg++;
	if (iarg == argc)
	    usage(argv[0]);
    }

    float *light_source;
    
    if (strcmp(argv[iarg], "-D65") == 0)
	light_source = cie_d65;
    else if (strcmp(argv[iarg], "-A") == 0)
	light_source = cie_a;
    else if (strcmp(argv[iarg], "-n") == 0)
	light_source = neutral_source;
    else if (strcmp(argv[iarg], "-K") == 0)
    {
	iarg++;
	if (iarg == argc)
	    usage(argv[0]);

	int temp = strtol(argv[iarg], NULL, 0);
	light_source = sed_blackbody(temp);
    }
    else
	usage(argv[0]);

    if (gmcc_mode)
	print_gmcc_colors(light_source);
    else
    {
 	float k = xyz_get_k_from_s(light_source);
 	print_rgb_of_sed(light_source, k);
    }

    exit(EXIT_SUCCESS);
}


	


