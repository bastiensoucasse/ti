#ifndef CONVOL1D_H
#define CONVOL1D_H

extern float *convol1d_swap_ij(float *channel, int width, int height);
extern float *convol1d_apply_3(float *channel, int width, int height, float kernel[3]);

#endif  /* CONVOL1D_H */

