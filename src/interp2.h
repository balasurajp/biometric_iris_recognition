#ifndef INTERP2_H
#define INTERP2_H

#include<iostream>
#include"opencv2\opencv.hpp"


using namespace cv;
class Interp2
{
public:
	Mat interp2(Mat image, Mat X1, Mat Y1);
};

#endif;
