#include"adjgamma.h"

Mat Adjgamma::adjustgamma(Mat image, double gamma) 
{
	if (gamma <= 0)
	{
		std::cout<<"Gamma value must be > 0"<<std::endl;
		exit(EXIT_FAILURE);
		
	}

	

	/*if (image.type != CV_64FC1)
	{
		image.convertTo(image, CV_64FC1);
		std::cout << "error not recieving gray scale image > 0" << std::endl;
	}*/

	double min, max;
	minMaxLoc(image, &min, &max);
	Mat newimage;
	newimage = image - min;
	newimage = image / max;

	gamma = 1 / gamma;

	pow(newimage, gamma, newimage);

	return newimage;





}