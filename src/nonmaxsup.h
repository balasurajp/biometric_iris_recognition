#ifndef NONMAXSUP_H
#define NONMAXSUP_H

#include<iostream>
#include"opencv2\opencv.hpp"


using namespace cv;
class Nonmaxsup
{
public:
	Mat nonmaxup(Mat inimage,Mat orient,double radius);
};

#endif;