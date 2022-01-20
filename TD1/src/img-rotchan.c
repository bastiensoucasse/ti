#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>

#define FMT IMG_FMT_RGB24

int main(int argc, char **argv)
{
    if (argc != 3)
        fprintf(stderr, "Usage: img-rotchan INPUT_IMAGE OUTPUT_IMAGE\n"), exit(EXIT_FAILURE);

    int x_size, y_size;
    unsigned char *pix = img_load_pixels(argv[1], &x_size, &y_size, FMT);
    if (!pix)
        fprintf(stderr, "img-rotchan: cannot load %s\n", argv[1]), exit(EXIT_FAILURE);

    int img_size = x_size * y_size;
    // unsigned char tmp;
    // for (int i = 0; i < 3*img_size; i += 3)
    // {
    //     tmp = pix[i+2];
    //     pix[i+2] = pix[i+1];
    //     pix[i+1] = pix[i];
    //     pix[i] = tmp; 
    // }

    unsigned char tmp;
    for (unsigned char *p = pix; p < pix + 3*img_size; p += 3)
    {
        tmp = *(p+2);
        *(p+2) = *(p+1);
        *(p+1) = *p;
        *p = tmp;
    }
       
    img_save_pixels(argv[2], pix, x_size, y_size, FMT);

    img_free_pixels(pix);
    return EXIT_SUCCESS;
}
