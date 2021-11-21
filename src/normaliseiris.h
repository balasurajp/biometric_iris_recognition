#ifndef NORMALISEIRIS_H
#define NORMALISEIRIS_H

#include<iostream>
#include"opencv2\opencv.hpp"
#include"cmath"

using namespace cv;
class Normaliseiris
{
public:
	Mat polar_array;
	Mat polar_noise;
	void normaliseiris(Mat image,int x_iris,int y_iris,int r_iris,int x_pupil,int y_pupil,int r_pupil,String eyeimage_filename,int radipixels,int angulardiv);
};

#endif;