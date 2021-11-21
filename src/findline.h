#ifndef FINDLINE_H
#define FINDLINE_H
#include<iostream>
#include"opencv2\opencv.hpp"
#include"nonmaxsup.h"
#include <ctime>
#include"adjgamma.h"
#include "hysthresh.h"
#include "canny.h"
#include "opencv2/highgui.hpp"
#include "radon.h"


using namespace cv;

class Findline
{
public:
	Mat findline(Mat image);

};

#endif