#ifndef RADON_H
#define RADON_H
#include<opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<iostream>
#include<math.h>
using namespace cv;
using namespace std;

class Radon
{
public:
	void radon(Mat image);

};

#endif
