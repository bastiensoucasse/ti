#include "bbox.h"

#include <assert.h>

static int
L_clamp(int v, const int min, const int max)
{
    if (v < min)
        v = min;
    else if (v > max)
        v = max;
    return v;
}

struct bbox
bbox_init(const int width, const int height, const int i, const int j, const int half_width)
{
    assert(half_width >= 0);

    const int i_min = L_clamp(i - half_width, 0, height - 1);
    const int i_max = L_clamp(i + half_width, 0, height - 1);
    const int j_min = L_clamp(j - half_width, 0, width - 1);
    const int j_max = L_clamp(j + half_width, 0, width - 1);

    return (struct bbox) { i_min, i_max, j_min, j_max };
}
