#ifndef SEGMENTIRIS_H
#define SEGMENTIRIS_H

#include "findline.h"
#include "findcircle.h"

using namespace cv;
class Segmentiris
{
public:

	Mat ycoordI;
	Mat xcoordI;
	Mat circleiris;
	Mat circlepupil;
	Mat imagewithnoise;

	void segmentiris(Mat eyeimage);
};

#endif;
