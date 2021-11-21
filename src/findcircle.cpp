#include "findcircle.h"

Mat Findcircle::findcircle(Mat eyeimage, int lradius, int uradius, float scaling, float sigma, float hithres, float lowthres, float vert, float horz)
{
	

	int lradsc = round(lradius*scaling);
	int uradsc = round(uradius*scaling);

	Cannyeye canny;
	canny.CannyreturnGradient(eyeimage,sigma,scaling, vert,horz);
	Mat Gradient = canny.Gradient;
	Mat or = canny. or ;



	Adjgamma gamma;

	Mat afterGamma = gamma.adjustgamma(Gradient, 1.9);

	Nonmaxsup nonmaxsup;
	Mat I4 = nonmaxsup.nonmaxup(afterGamma, or , 1.5);



	//Mat piGradient = I4(Range(0, 11), Range(0, 11));
	//std::cout << piGradient << std::endl;

	Hysthresh hysthresh;
	Mat edgeimage = hysthresh.hysthresh(I4, hithres, lowthres);

	/*	FileStorage fs("test.yml", FileStorage::WRITE);
	fs << "mat" << edgeimage;
	fs.release();*/

	Houghcircle hough;

	Mat h = hough.hough(edgeimage, lradsc, uradsc);

	
	
	
	double testMaxval;
	int maxIdx[3];
	minMaxIdx(h, 0, &testMaxval, 0, maxIdx);
	
	Mat ret(1,3,CV_32S);

	int row = maxIdx[0];
	int col = maxIdx[1] % (edgeimage.cols);
	int r = maxIdx[1] / (edgeimage.cols);

	ret.at<int>(0) = round((row+1) / scaling)-1;
	ret.at<int>(1) = round((col+1) / scaling)-1;
	ret.at<int>(2) = round((lradsc + r+1) / scaling);

	
	return  ret;
	
}
