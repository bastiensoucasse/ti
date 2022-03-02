#include <assert.h>

#include "bbox.h"

static int
L_clamp(int v, int min, int max)
{
    if (v < min)
	v = min;
    else if (v > max)
	v = max;
    return v;
}

struct bbox
bbox_init(int width, int height, int i, int j, int half_width)
{
    assert(half_width >= 0);

    int i_min = L_clamp(i - half_width, 0, height - 1);
    int i_max = L_clamp(i + half_width, 0, height - 1);
    int j_min = L_clamp(j - half_width, 0, width - 1);
    int j_max = L_clamp(j + half_width, 0, width - 1);

    return (struct bbox) { i_min, i_max, j_min, j_max };
}
