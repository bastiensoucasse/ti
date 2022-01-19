#ifndef TOOLS_H
#define TOOLS_H

#include <stdlib.h>

const char *channel_extract(const char *pixels, const size_t size, const unsigned int channel_number);

const char *channel_compose(const char *r_chan, const char *g_chan, const char *b_chan, const size_t size);

#endif // TOOLS_H
