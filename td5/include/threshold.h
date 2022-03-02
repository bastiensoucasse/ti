#ifndef THRESHOLD_H
#define THRESHOLD_H

extern unsigned char* threshold_std(unsigned char* channel, int size, unsigned char th);
extern unsigned char* threshold_mean(unsigned char* channel, int size);
extern unsigned char* threshold_median(unsigned char* channel, int size);
extern unsigned char* threshold_lmean(unsigned char* channel, int width, int height, int half_width);
extern unsigned char* threshold_percent(unsigned char* channel, int size, float percent);

#endif // THRESHOLD_H
