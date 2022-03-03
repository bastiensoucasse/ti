#ifndef BBOX_H
#define BBOX_H

struct bbox {
    int imin;
    int imax;
    int jmin;
    int jmax;
};

extern struct bbox
bbox_init(const int width, const int height, const int i, const int j, const int half_width);

#endif // BBOX_H
