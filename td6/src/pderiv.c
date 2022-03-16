#include "pderiv.h"

#include <stdio.h>
#include <stdlib.h>

#include "convol1d.h"

static float kernel[3] = { 0.0, -1.0, 1.0 };
static float kernel_deriv[3] = { -1.0, 0.0, 1.0 };
static float kernel_smooth1[3] = { 1.0, 1.0, 1.0 };
static float kernel_smooth2[3] = { 1.0, 2.0, 1.0 };

// static float*
// truc(float k1[3], float k2[3])
// {
//     float *k = (float *)malloc(sizeof(float) * 9);
//     for (int i = 0; i < 3; i++)
//         for (int j = 0; j < 3; j++)
//             k[i * 3 + j] = k1[i] * k2[j];

//     for (int i = 0; i < 9; i++)
//         printf("%f\n", k[i]);
//     return k;
// }

float*
pderiv_d2_dj(float* channel, int width, int height)
{
    return convol1d_apply_3(channel, width, height, kernel);
}

float*
pderiv_d2_di(float* channel, int width, int height)
{
    float* ch_1 = convol1d_swap_ij(channel, width, height);
    float* ch_2 = convol1d_apply_3(ch_1, height, width, kernel);
    float* result = convol1d_swap_ij(ch_2, height, width);
    free(ch_1);
    free(ch_2);
    return result;
}

float*
pderiv_d3_dj(float* channel, int width, int height)
{
    return convol1d_apply_3(channel, width, height, kernel_deriv);
}

float*
pderiv_d3_di(float* channel, int width, int height)
{
    float* ch_1 = convol1d_swap_ij(channel, width, height);
    float* ch_2 = convol1d_apply_3(ch_1, height, width, kernel_deriv);
    float* result = convol1d_swap_ij(ch_2, height, width);
    free(ch_1);
    free(ch_2);
    return result;
}

float*
pderiv_prewitt_dj(float* channel, int width, int height)
{
    float* deriv = convol1d_apply_3(channel, width, height, kernel_deriv);
    float* deriv_inv = convol1d_swap_ij(deriv, width, height);
    float* smooth = convol1d_apply_3(deriv_inv, width, height, kernel_smooth1);
    float* smooth_inv = convol1d_swap_ij(smooth, width, height);
    free(deriv);
    free(deriv_inv);
    free(smooth);
    return smooth_inv;
}

float*
pderiv_prewitt_di(float* channel, int width, int height)
{
    // Lissage horizontal
    float* ch_1 = convol1d_apply_3(channel, width, height, kernel_smooth1);

    // Dérivation verticale
    float* ch_2 = convol1d_swap_ij(ch_1, width, height);
    float* ch_3 = convol1d_apply_3(ch_2, height, width, kernel_deriv);
    float* result = convol1d_swap_ij(ch_3, height, width);

    free(ch_1);
    free(ch_2);
    free(ch_3);

    return result;
}

float*
pderiv_sobel_dj(float* channel, int width, int height)
{
    float* deriv = convol1d_apply_3(channel, width, height, kernel_deriv);
    float* deriv_inv = convol1d_swap_ij(deriv, width, height);
    float* smooth = convol1d_apply_3(deriv_inv, width, height, kernel_smooth2);
    float* smooth_inv = convol1d_swap_ij(smooth, width, height);
    free(deriv);
    free(deriv_inv);
    free(smooth);
    return smooth_inv;
}

float*
pderiv_sobel_di(float* channel, int width, int height)
{
    // Lissage horizontal
    float* ch_1 = convol1d_apply_3(channel, width, height, kernel_smooth2);

    // Dérivation verticale
    float* ch_2 = convol1d_swap_ij(ch_1, width, height);
    float* ch_3 = convol1d_apply_3(ch_2, height, width, kernel_deriv);
    float* result = convol1d_swap_ij(ch_3, height, width);

    free(ch_1);
    free(ch_2);
    free(ch_3);

    return result;
}

float*
pderiv_deriche_di(float* channel, int width, int height, float alpha)
{
    // TODO
}

float*
pderiv_deriche_dj(float* channel, int width, int height, float alpha)
{
    // TODO
}
