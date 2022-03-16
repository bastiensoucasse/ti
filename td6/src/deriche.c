#include <stdlib.h>
#include <math.h>

#include "deriche.h"

static float d_a;
static float d_b1;
static float d_b2;

static float s_a0;
static float s_a1;
static float s_a2;
static float s_a3;
static float s_b1;
static float s_b2;

static void
init_parameters(float alpha)
{
    d_a = (1-exp(-alpha))*(1-exp(-alpha));
    d_b1 = 2*exp(-alpha);
    d_b2 = -exp(-2*alpha);

    float k = ((1 - exp(-alpha))*(1-exp(-alpha))) / (1 + 2*alpha*exp(-alpha) - exp(-2*alpha));
    
    s_a0 = k;
    s_a1 = k*(alpha - 1)*exp(-alpha);
    s_a2 = k*(alpha + 1)*exp(-alpha);
    s_a3 = -k*exp(-2*alpha);
    s_b1 = 2*exp(-alpha);
    s_b2 = -exp(-2*alpha);
}

static void
d_process_line(float *il, float *idl, int size)
{
    float ip[size];
    float im[size];

    ip[0] = il[0];
    ip[1] = il[1];
    for (int t = 2; t < size ; t++)
	ip[t] = il[t-1] + d_b1*ip[t-1] + d_b2*ip[t-2];

    im[size-1] = il[size-1];
    im[size-2] = il[size-2];
    for (int t = size-3; t >= 0; t--)
	im[t] = il[t+1] + d_b1*im[t+1] + d_b2*im[t+2];

    for (int t = 0; t < size; t++)
	idl[t] =  d_a*(ip[t] - im[t]);
}
	
static void
s_process_line(float *il, float *idl, int size)
{
    float ip[size];
    float im[size];

    ip[0] = il[0];
    ip[1] = il[1];
    for (int t = 2; t < size ; t++)
	ip[t] = s_a0*il[t] + s_a1*il[t-1] + s_b1*ip[t-1] + s_b2*ip[t-2];

    im[size-1] = il[size-1];
    im[size-2] = il[size-2];
    for (int t = size-3; t >= 0; t--)
	im[t] = s_a2*il[t+1] + s_a3*il[t+2] + s_b1*im[t+1] + s_b2*im[t+2];

    for (int t = 0; t < size; t++)
	idl[t] =  d_a*(ip[t] + im[t]);
}

float *
deriche_apply_s(float *channel, int width, int height, float alpha)
{
    init_parameters(alpha);
    
    float *result = malloc(width*height*sizeof(float));
    float *pr = result;

    for (int i = 0; i < height; i++)
    {
	s_process_line(channel, pr, width);
	channel += width;
	pr += width;
    }

    return result;
}

float *
deriche_apply_d(float *channel, int width, int height, float alpha)
{
    init_parameters(alpha);
    
    float *result = malloc(width*height*sizeof(float));
    float *pr = result;

    for (int i = 0; i < height; i++)
    {
	d_process_line(channel, pr, width);
	channel += width;
	pr += width;
    }

    return result;
}


    



  
