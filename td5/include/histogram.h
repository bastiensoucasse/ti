#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define HISTOGRAM_NLEV 256

extern float*
histogram_make(const unsigned char* const channel, const int size);

extern float*
histogram_make_local(const unsigned char* const channel, const int width, const int height, const int i, const int j, const int half_width);

extern float*
histogram_tdup(const float* const histogram);

extern void
histogram_cumulate(float* const histogram);

extern void
histogram_normalize(float* const histogram);

#endif // HISTOGRAM_H
