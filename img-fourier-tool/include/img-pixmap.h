#ifndef IMG_PIXMAP_H
#define IMG_PIXMAP_H

#include <imago2.h>

extern struct img_pixmap*
img_pixmap_read(const char* const path);

extern void
img_pixmap_save(unsigned char* const pixels, const int width, const int height, const char* const path);

#endif // IMG_PIXMAP_H
