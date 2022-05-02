#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fft.h"
#include "fip.h"
#include "img-pixmap.h"

static void
usage(FILE* const output, const char* const launcher)
{
    fprintf(output, "Usage: %s <option>…\n"
                    "\n"
                    "Options:\n"
                    "    -e, --encode    Generates the frequency data of an image (FFT):\n"
                    "                    …<image> <amplitude_spectrum> <phase_spectrum>.\n"
                    "\n"
                    "    -d, --decode    Generates an image from its frequency data (IFFT):\n"
                    "                    …<amplitude_spectrum> <phase_spectrum> <image>.\n",
        launcher);
}

static void
encode(const char* const input_img_path, const char* const amplitude_output_path, const char* const phase_output_path)
{
    printf("Encoding \"%s\" into \"%s\" & \"%s\"…\n", input_img_path, amplitude_output_path, phase_output_path);
    struct img_pixmap* const img = img_pixmap_read(input_img_path);

    fftw_complex* const frequency_channel = fft_forward(img->pixels, img->width, img->height);
    double* const amplitude_spectrum_channel = fft_extract_as(frequency_channel, img->width, img->height);
    double* const phase_spectrum_channel = fft_extract_ps(frequency_channel, img->width, img->height);

    fip_save_img_spectrum(amplitude_spectrum_channel, img->width, img->height, amplitude_output_path, false);
    fip_save_img_spectrum(phase_spectrum_channel, img->width, img->height, phase_output_path, true);

    img_destroy(img);
    fftw_free(frequency_channel);
    free(amplitude_spectrum_channel);
    free(phase_spectrum_channel);
}

static void
decode(const char* const amplitude_spectrum_path, const char* const phase_spectrum_path, const char* const img_path)
{
    printf("Decoding \"%s\" & \"%s\" into \"%s\"…\n", amplitude_spectrum_path, phase_spectrum_path, img_path);
    struct img_pixmap* const amplitude_spectrum_img = img_pixmap_read(amplitude_spectrum_path);
    struct img_pixmap* const phase_spectrum_img = img_pixmap_read(phase_spectrum_path);

    assert(amplitude_spectrum_img->width == phase_spectrum_img->width);
    assert(amplitude_spectrum_img->height == phase_spectrum_img->height);

    const int width = amplitude_spectrum_img->width;
    const int height = amplitude_spectrum_img->height;

    const double* const amplitude_spectrum_channel = fip_get_spectrum_from_pixels(amplitude_spectrum_img->pixels, width, height, false);
    const double* const phase_spectrum_channel = fip_get_spectrum_from_pixels(phase_spectrum_img->pixels, width, height, true);

    fftw_complex* const frequency_channel = fft_compose_aps(amplitude_spectrum_channel, phase_spectrum_channel, width, height);
    unsigned char* const img_channel = fft_backward(frequency_channel, width, height);

    img_pixmap_save(img_channel, width, height, img_path);

    img_destroy(amplitude_spectrum_img);
    img_destroy(phase_spectrum_img);
    fftw_free(frequency_channel);
    free(img_channel);
}

int main(const int argc, const char* const* const argv)
{
    if (argc != 5) {
        usage(stderr, argv[0]);
        exit(EXIT_FAILURE);
    }

    if (!strcmp(argv[1], "-e") || !strcmp(argv[1], "--encode"))
        encode(argv[2], argv[3], argv[4]);
    else if (!strcmp(argv[1], "-d") || !strcmp(argv[1], "--decode"))
        decode(argv[2], argv[3], argv[4]);
    else if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help"))
        usage(stdout, argv[0]);
    else {
        usage(stderr, argv[0]);
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
