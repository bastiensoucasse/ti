#ifndef STIF_H
#define STIF_H

extern float
stif_mean(const unsigned char* const channel, const int size);

extern float
stif_lmean(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width);

extern int
stif_median(const unsigned char* const channel, int const size);

extern int
stif_lmedian(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width);

extern float
stif_variance(const unsigned char* const channel, int const size);

extern float
stif_lvariance(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width);

extern float
stif_entropy(const unsigned char* const channel, const int size);

extern float
stif_lentropy(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width);

#endif // STIF_H
