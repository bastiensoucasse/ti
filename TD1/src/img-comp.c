#include "tools.h"

#include <stdio.h>
#include <stdlib.h>

int main(const int argc, const char **argv)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: img-comp RCHAN_INPUT GCHAN_INPUT BCHAN_INPUT OUTPUT_IMAGE\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
