#ifndef ADJGAMMA_H
#define ADJGAMMA_H
#include<iostream>
#include"opencv2\opencv.hpp"
#include <stdlib.h>

using namespace cv;

class Adjgamma
{
public:
	Mat adjustgamma(Mat image,double gamma);

};

#endif;