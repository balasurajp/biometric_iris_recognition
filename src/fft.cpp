#include "fft.h"

void Fft::fft(fftw_complex * in, fftw_complex * out)
{
	// create a DFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
}

void Fft::ifft(fftw_complex * in, fftw_complex * out)
{
	// create an IDFT plan
	fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_BACKWARD, FFTW_ESTIMATE);
	// execute the plan
	fftw_execute(plan);
	// do some cleaning
	fftw_destroy_plan(plan);
	fftw_cleanup();
	// scale the output to obtain the exact inverse
	for (int i = 0; i < N; ++i) {
		out[i][REAL] /= N;
		out[i][IMAG] /= N;
	}
}

void Fft::displayComplex(fftw_complex * y)
{
	for (int i = 0; i < N; ++i)
		if (y[i][IMAG] < 0)
			cout << y[i][REAL] << " - " << abs(y[i][IMAG]) << "i" << endl;
		else
			cout << y[i][REAL] << " + " << y[i][IMAG] << "i" << endl;
}

void Fft::displayReal(fftw_complex * y)
{
	for (int i = 0; i < N; ++i)
		cout << y[i][REAL] << endl;
}
