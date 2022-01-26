#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colorimetric_data.h"
#include "sed.h"

#include "MISSINGCODE.h"

float*
sed_alloc(void)
{
    float* sed = malloc(SED_SIZE * sizeof(float));

    return sed;
}

void sed_copy(float* dst, float* src)
{
    memcpy(dst, src, SED_SIZE * sizeof(float));
}

float*
sed_dup(float* sed)
{
    float* result = sed_alloc();

    sed_copy(result, sed);
    return result;
}

float sed_sum(float* sed)
{
    float area = 0.0;
    int i;

    for (i = 0; i < SED_SIZE; i++)
        area += sed[i];

    return area * SED_LAMBDA_STEP;
}

void sed_multiply_by(float* e, float* f)
{
    for (int i = 0; i < SED_SIZE; i++)
        e[i] = e[i] * f[i];
}

float*
sed_blackbody(int temperature)
{
    assert(temperature >= 0.0);
    float* result = sed_alloc();

    double c1 = 3.7415e29;
    double c2 = 1.4388e7;

    double alpha = pow(560, 5) * (exp(c2 / (560 * temperature)) - 1) / c1;

    int lambda;
    for (int i = 0; i < SED_SIZE; i++) {
        lambda = SED_LAMBDA_MIN + (i * SED_LAMBDA_STEP);
        result[i] = alpha * c1 / (pow(lambda, 5) * (exp(c2 / (lambda * temperature)) - 1));
    }

    return result;
}