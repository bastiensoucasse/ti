#ifndef THRESHOLD_H
#define THRESHOLD_H

extern unsigned char*
threshold_std(const unsigned char* const channel, const int size, const unsigned char th);

extern unsigned char*
threshold_mean(const unsigned char* const channel, const int size);

extern unsigned char*
threshold_median(const unsigned char* const channel, const int size);

extern unsigned char*
threshold_lmean(const unsigned char* const channel, const int width, const int height, const int half_width);

extern unsigned char*
threshold_percent(const unsigned char* const channel, const int size, const float percent);

#endif // THRESHOLD_H
