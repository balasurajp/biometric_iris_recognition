#ifndef GABORCONVOLVE_H
#define GABORCONVOLVE_H

#include<iostream>
#include"opencv2\opencv.hpp"
#include"cmath"
#include "fft.h"


using namespace cv;
class Gaborconvolve
{
public:

	

	fftw_complex result[M][N];
	Mat  filtersum2;
	void gaborconvolve(Mat image , int n_scales, int minWaveLength , int mult, double sigmaOnf);
	Mat H1r;
	Mat H2r;
};

#endif;

