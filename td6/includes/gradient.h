#ifndef GRADIENT_H
#define GRADIENT_H

extern float *gradient_norm_abs(float *di_channel, float *dj_channel, int size);
extern float *gradient_norm_eucl(float *di_channel, float *dj_channel, int size);
extern float *gradient_norm_max(float *di_channel, float *dj_channel, int size);

extern float *gradient_local_max(float *di_channel, float *dj_channel, int width, int height);

#endif  /* GRADIENT_H */
