#ifndef ADDCIRCLE_H
#define ADDCIRCLE_H

#include<iostream>
#include"opencv2\opencv.hpp"


using namespace cv;
class Addcircle
{
public:
	Mat addcircle(int rows,int cols, int cx, int cy,int radius,int weight);
};

#endif;