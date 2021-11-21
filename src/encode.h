#ifndef ENCODE_H
#define ENCODE_H

#include<iostream>
#include"opencv2\opencv.hpp"
#include"cmath"
#include "fft.h"

using namespace cv;
class Encode
{
public:
	
	void encode(Mat polar_array, Mat noise_array, int n_scales, int minWaveLength,int mult,double sigmaOnf);



};

#endif;
