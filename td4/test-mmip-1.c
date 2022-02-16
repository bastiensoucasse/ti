#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include <complex.h>
#include <fftw3.h>
#include <imago2.h>

#include "mmip.h"

static void
usage(char *s)
{
    fprintf(stderr, "Usage: %s {-e|-d|-o|-c} RADIUS INPUT OUTPUT\n" , s);
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

    if (argc != 5)
	usage(argv[0]);

    char *op = argv[1];
    int radius = atoi(argv[2]);
    char *input_file = argv[3];
    char *output_file = argv[4];

    struct img_pixmap *img = img_pixmap_read(input_file);
    unsigned char *img_buffer = (unsigned char *) img->pixels;
    int width = img->width;
    int height = img->height;

    unsigned char *result = NULL;
    
    if (strcmp(op, "-e") == 0)
	result = mmip_disk_erosion(img_buffer, width, height, radius);
    else if (strcmp(op, "-d") == 0)
	result = mmip_disk_dilatation(img_buffer, width, height, radius);
    else if (strcmp(op, "-o") == 0)
	result = mmip_disk_opening(img_buffer, width, height, radius);
    else if (strcmp(op, "-c") == 0)
	result = mmip_disk_closing(img_buffer, width, height, radius);
    else
    {
	fprintf(stderr, "%s: unknowm otion (must be -e, -d, -o or -c)", op);
	exit(EXIT_FAILURE);
    }

    memcpy(img_buffer, result, width*height*img->pixelsz);
    img_save(img, output_file);

    free(result);
    img_free(img);

    exit(EXIT_SUCCESS);
}
