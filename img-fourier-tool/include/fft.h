#ifndef FFT_H
#define FFT_H

#include <complex.h>
#include <fftw3.h>

extern fftw_complex*
fft_forward(const unsigned char* const chan, const int width, const int height);

extern unsigned char*
fft_backward(fftw_complex* const fr_chan, const int width, const int height);

extern double*
fft_extract_as(const fftw_complex* const fr_chan, const int width, const int height);

extern double*
fft_extract_ps(const fftw_complex* const fr_chan, const int width, const int height);

extern fftw_complex*
fft_compose_aps(const double* const as, const double* const ps, const int width, const int height);

#endif // FFT_H
