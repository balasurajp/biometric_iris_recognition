#ifndef CANNY_H
#define CANNY_H

#include<iostream>
#include"opencv2\opencv.hpp"

using namespace cv;

class Cannyeye
{
public:

	Mat or ;
	Mat Gradient;
	void CannyreturnGradient(Mat im, double sigma, double scaling, double vert, double horz);

private:

	Mat GaussianKernel(int ksize, double sigma, int ktype);

	Mat ReturnH(Mat scaledgblur, int rows, int cols);

	Mat ReturnV(Mat scaledgblur, int rows, int cols);

	Mat ReturnD1(Mat scaledgblur, int rows, int cols);

	Mat ReturnD2(Mat scaledgblur, int rows, int cols);

};
#endif;