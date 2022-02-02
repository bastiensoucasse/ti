#ifndef FFT_H
#define FFT_H

#include <complex.h>
#include <fftw3.h>

/*
  This function computes a forward discrete Fourier transform of the
  spatial representation of the image channel of address CHAN and of
  size WIDTH x HEIGHT. The function returns the result of the
  transformation as an array of complex numbers of the same size,
  allocated with fftw_malloc function. Thus the liberation of this
  area memory must be done with fftw_free function.
*/
extern fftw_complex* fft_forward(unsigned char* chan, int width, int height);

/*
  This function computes a backward discrete Fourier transform of the
  complex frequency representation of the image channel of address FR_CHAN
  and size WIDTH x HEIGHT. The function returns the result of the transformation
  as an array of unsigned chars of the same size, allocated with
  standard malloc function.
*/
extern unsigned char* fft_backward(fftw_complex* fr_chan, int width, int height);

/*
  This function extract the amplitude spectrum of the complex frequency
  representation of the image channel of address FR_CHAN and size WIDTH x
  HEIGHT. The function returns the spectrum as an array of double
  floating points of the same size, allocated with standard malloc
  function.
*/
extern double* fft_extract_as(fftw_complex* fr_chan, int width, int height);

/*
  This function extract the phase spectrum of the complex frequency
  representation of the image channel of address FR_CHAN and size WIDTH x
  HEIGHT. The function returns the spectrum as an array of double
  floating points of the same size, allocated with standard malloc
  function.

*/
extern double* fft_extract_ps(fftw_complex* fr_chan, int width, int height);

/*
  This function build a complex frequency representation from the
  amplitude spectrum AS and the phase spectrum PS. Arrays are assumed
  to be of size WIDTH x HEIGHT. The function returns the result of the
  reconstruction as an array of unsigned chars of the same size,
  allocated with standard malloc function.
*/
extern fftw_complex* fft_compose_aps(double* as, double* ps, int width, int height);

#endif /* FFT_H */
