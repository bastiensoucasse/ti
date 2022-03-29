#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "gradient.h"

static int
L_octant(float theta)
{
    if (theta < 0)
        theta += M_PI;

    if (theta >= 0.0 && theta < M_PI / 8.0)
        return 1;

    if (theta >= M_PI / 8.0 && theta < 3.0 * M_PI / 8.0)
        return 2;

    if (theta >= 3.0 * M_PI / 8.0 && theta < 5.0 * M_PI / 8.0)
        return 3;

    if (theta >= 5.0 * M_PI / 8.0 && theta < 7.0 * M_PI / 8.0)
        return 4;

    if (theta >= 7.0 * M_PI / 8.0 && theta < 9.0 * M_PI / 8.0)
        return 1;

    if (theta >= 9.0 * M_PI / 8.0 && theta < 11.0 * M_PI / 8.0)
        return 2;

    if (theta >= 11.0 * M_PI / 8.0 && theta < 13.0 * M_PI / 8.0)
        return 3;

    if (theta >= 13.0 * M_PI / 8.0 && theta < 15.0 * M_PI / 8.0)
        return 4;

    // theta in [15/8 * M_PI, 2 * M_PI]
    return 1;
}

// static int
// angular_sector(float di, float dj)
// {
//     float theta = atan2(-di, dj);
//     float angle = M_M_PI / 8;
//     for (int k = 0; k < 8; k++)
//         if (angle + k*M_M_PI_4 <= theta && theta <= angle + (k+1)*M_M_PI_4)
//             return (k + 1)%4;
//     return -1;
// }

float*
gradient_norm_abs(float* di_channel, float* dj_channel, int size)
{
    float* norm = (float*)malloc(sizeof(float) * size);
    for (int x = 0; x < size; x++)
        norm[x] = fabsf(di_channel[x]) + fabsf(dj_channel[x]);

    return norm;
}

float*
gradient_norm_eucl(float* di_channel, float* dj_channel, int size)
{
    float* norm = (float*)malloc(sizeof(float) * size);
    for (int x = 0; x < size; x++)
        norm[x] = sqrt(pow(di_channel[x], 2) + pow(dj_channel[x], 2));

    return norm;
}

float*
gradient_norm_max(float* di_channel, float* dj_channel, int size)
{
    float* norm = (float*)malloc(sizeof(float) * size);
    for (int x = 0; x < size; x++)
        norm[x] = fmax(fabsf(di_channel[x]), fabsf(dj_channel[x]));

    return norm;
}

float*
gradient_local_max(float* di_channel, float* dj_channel, int width, int height)
{
    float* loc_max = (float*)malloc(sizeof(float) * width * height);

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            int p = i * width + j;
            int p1, p2;

            int sector = L_octant(atan2(-di_channel[p], dj_channel[p]));
            switch (sector) {
            case 1:
                p1 = (i - 1) * width + j + 1;
                p2 = (i + 1) * width + j - 1;
                break;
            case 2:
                p1 = (i - 1) * width + j;
                p2 = (i + 1) * width + j;
                break;
            case 3:
                p1 = (i - 1) * width + j - 1;
                p2 = (i + 1) * width + j + 1;
                break;
            case 4:
                p1 = i * width + j + 1;
                p2 = i * width + j - 1;
                break;
            default:
                fprintf(stderr, "Invalid angular sector.\n");
                exit(EXIT_FAILURE);
                break;
            }

            float p_norm = sqrt(pow(di_channel[p], 2) + pow(dj_channel[p], 2));
            float p1_norm = sqrt(pow(di_channel[p1], 2) + pow(dj_channel[p1], 2));
            float p2_norm = sqrt(pow(di_channel[p2], 2) + pow(dj_channel[p2], 2));

            loc_max[p] = p_norm > p1_norm && p_norm > p2_norm ? p_norm : 0;
        }

    return loc_max;
}
