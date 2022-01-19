#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>
#include <math.h>

#define FMT IMG_FMT_RGBA32

int f(int x, int a)
{
    return a*x + (2*(1-a)*x*x) / (1+x*x);
}

int main(int argc, char **argv)
{
    if (argc != 8)
    {
        fprintf(stderr, "Usage: img-gummira WIDTH A B X_0 Y_0 N OUTPUT_IMAGE\n");
        exit(EXIT_FAILURE);
    }

    printf("yo\n");
    struct img_pixmap *img = img_create();

    printf("salut\n");
    int w = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    int x_0 = atoi(argv[4]);
    int y_0 = atoi(argv[5]);
    int n = atoi(argv[6]);

    printf("ca va ?\n");
    unsigned char pix[4*w];

    printf("ouais\n");
    int x[n], y[n];
    int mx = x_0, my = y_0;
    for (int i = 0; i < n-1; i++)
    {
        // printf("hey\n");
        x[i+1] = b * y[i] + f(x[i], a);
        y[i] = -x[i] + f(x[i+1], a);

        mx = x[i+1] > mx ? x[i+1] : mx;
        my = y[i+1]> my ? y[i+1] : my;
    }

    int M = mx > my ? mx : my;
    int alpha;
    unsigned char rgba[4] = {255, 0, 0, 0};
    for (int i = 0; i < n; i++)
    {
        printf("hey encore\n");
        int tx = x[i]/M, ty = y[i]/M;
        alpha = 1 - (1/sqrt(2)) * sqrt(tx*tx + ty*ty);

        rgba[1] = alpha * 255;
        rgba[2] = alpha * alpha * 255;
        rgba[3] = rgba[2];

        img_setpixel(img, x[i], y[i], rgba);
    }

    img_set_pixels(img, w, w, FMT, pix);
    img_save(img, argv[7]);

    printf("coucou\n");

    img_free(img);
    return EXIT_SUCCESS;
}

// ./build/img-gummira 81000 -5355 1 1 1 80000 output/img-gummira/test.jpeg