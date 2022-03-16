#ifndef PDERIV_H
#define PDERIV_H

extern float *pderiv_d2_di(float *channel, int width, int height);
extern float *pderiv_d2_dj(float *channel, int width, int height);

extern float *pderiv_d3_di(float *channel, int width, int height);
extern float *pderiv_d3_dj(float *channel, int width, int height);

extern float *pderiv_prewitt_di(float *channel, int width, int height);
extern float *pderiv_prewitt_dj(float *channel, int width, int height);

extern float *pderiv_sobel_di(float *channel, int width, int height);
extern float *pderiv_sobel_dj(float *channel, int width, int height);

extern float *pderiv_deriche_di(float *channel, int width, int height, float alpha);
extern float *pderiv_deriche_dj(float *channel, int width, int height, float alpha);

#endif  /* PDERIV_H */
