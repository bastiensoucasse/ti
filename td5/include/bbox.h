#ifndef BBOX_H
#define BBOX_H

struct bbox {
    int imin;
    int imax;
    int jmin;
    int jmax;
};

extern struct bbox
bbox_init(int width, int height, int i, int j, int half_width);

#endif // BBOX_H
