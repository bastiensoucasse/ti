#include <stdio.h>
#include <stdlib.h>
#include <imago2.h>
#include <math.h>

#define FMT IMG_FMT_RGBA32

float f(float x, float a)
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

    struct img_pixmap *img = img_create();

    unsigned int w = atoi(argv[1]);
    float a = atof(argv[2]);
    float b = atof(argv[3]);
    float x_0 = atof(argv[4]);
    float y_0 = atof(argv[5]);
    unsigned int n = atoi(argv[6]);

    unsigned char *pix = (unsigned char *)malloc(4 * w * w * sizeof(unsigned char));
    img_set_pixels(img, w, w, FMT, pix);

    float x[n], y[n];
    x[0] = x_0, y[0] = y_0;
    float mx = fabs(x_0), my = fabs(y_0);
    for (int i = 0; i < n-1; i++)
    {
        x[i+1] = b * y[i] + f(x[i], a);
        y[i+1] = -x[i] + f(x[i+1], a);

        mx = fabs(x[i+1]) > mx ? fabs(x[i+1]) : mx;
        my = fabs(y[i+1])> my ? fabs(y[i+1]) : my;
    }

    float M = mx > my ? mx : my;
    float alpha;
    unsigned char rgba[4] = {255, 0, 0, 0};
    for (int i = 0; i < n; i++)
    {
        float tx = x[i]/M, ty = y[i]/M;
        alpha = 1.f - (1.f/sqrt(2.f)) * sqrt(tx*tx + ty*ty);

        rgba[1] = alpha * 255;
        rgba[2] = alpha * alpha * 255;
        rgba[3] = rgba[2];

        const unsigned int px = (w/2) * (tx+1);
        const unsigned int py = (w/2) * (ty+1);

        // const unsigned int px = (w/2) * (x[i]/mx+1);
        // const unsigned int py = (w/2) * (y[i]/my+1);

        img_setpixel(img, px, py, rgba);
    }

    img_save(img, argv[7]);

    img_free(img), free(pix);
    return EXIT_SUCCESS;
}

// Test: ./input/img-gummira-tests/mk-gummira-imgs.sh build/img-gummira 1000 1000000 output/img-gummira/test
