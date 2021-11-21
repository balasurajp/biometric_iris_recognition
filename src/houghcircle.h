#ifndef HOUGHCIRCLE_H
#define HOUGHCIRCLE_H

#include<iostream>
#include"opencv2\opencv.hpp"
using namespace cv;


class Houghcircle
{
public:
	Mat hough(Mat inmage, int rmin, int rmax);
};

#endif;