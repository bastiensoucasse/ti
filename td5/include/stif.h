#ifndef STIF_H
#define STIF_H

extern float stif_mean(unsigned char* channel, int size);
extern float stif_lmean(unsigned char* channel, int width, int height, int i, int j, int half_width);

extern float stif_variance(unsigned char* channel, int size);
extern float stif_lvariance(unsigned char* channel, int width, int height, int i, int j, int half_width);

extern float stif_entropy(unsigned char* channel, int size);
extern float stif_lentropy(unsigned char* channel, int width, int height, int i, int j, int half_width);

extern int stif_median(unsigned char* channel, int size);
extern int stif_lmedian(unsigned char* channel, int width, int height, int i, int j, int half_width);

#endif // STIF_H
