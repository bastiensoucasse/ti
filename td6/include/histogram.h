#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#define HISTOGRAM_NLEV 256

extern float*
histogram_make(unsigned char* channel, int size);

// extern float*
// histogram_make_local(unsigned char* channel, int width, int height, int i, int j, int half_width);

extern float*
histogram_tdup(float* hist);

extern void
histogram_cumulate(float* hist);

extern void
histogram_normalize(float* hist);

#endif // HISTOGRAM_H
