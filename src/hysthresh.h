#ifndef HYSTHRESH_H
#define HYSTHRESH_H
#include<iostream>
#include"opencv2\opencv.hpp"


using namespace cv;
class Hysthresh
{
public:
	Mat hysthresh(Mat im, double T1, double T2);
};

#endif;