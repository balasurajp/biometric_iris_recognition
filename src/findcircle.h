#include<iostream>
#include"opencv2\opencv.hpp"
#include"nonmaxsup.h"
#include <ctime>
#include"adjgamma.h"
#include "hysthresh.h"
#include "houghcircle.h"
#include "canny.h"
using namespace cv;


class Findcircle
{
public:
	Mat findcircle(Mat eyeimage, int lradius, int uradius,float scaling,float sigma,float hithres,float lowthres,float vert,float horz);

	
};




