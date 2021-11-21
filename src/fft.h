#ifndef FFT_H
#define FFT_H

#include <iostream>
#include <fftw3.h>

#define REAL 0
#define IMAG 1
#define N 240
#define M 20

using namespace std;

class Fft
{
public:

	void fft(fftw_complex *in, fftw_complex *out);
	void ifft(fftw_complex *in, fftw_complex *out);
	void displayComplex(fftw_complex *y);
	void displayReal(fftw_complex *y);
};

#endif;

