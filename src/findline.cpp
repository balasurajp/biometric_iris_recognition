#include "findline.h"

Mat Findline::findline(Mat image)
{
	Cannyeye canny;
	canny.CannyreturnGradient(image, 2, 1, 0.00, 1.00);

	Mat or= canny.or;
	Mat I2 = canny.Gradient;


	Adjgamma gamma;

	Mat I3 = gamma.adjustgamma(I2, 1.9);

	Nonmaxsup nonmaxsup;
	Mat I4 = nonmaxsup.nonmaxup(I3, or , 1.5);


	Hysthresh hysthresh;
	Mat edgeimage = hysthresh.hysthresh(I4, 0.20, 0.15);

	edgeimage.convertTo(edgeimage, CV_8U);
	edgeimage = edgeimage * 255;

	
	Mat mask = Mat::zeros(image.rows, image.cols, CV_32S);
	vector<Vec2f> lines;
	// detect lines
	HoughLines(edgeimage, lines, 1, CV_PI / 180, 50, 0, 0);

	
	// draw lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		
		line(mask, pt1, pt2, Scalar(1), 3, CV_AA);
	}
	
	
/*	for (int i = 0; i < mask.rows; i++) 
	{
		for (int j = 0; j < mask.cols; j++) 
		{
			if (mask.at<char>(i,j)==0)
			{
				std::cout << i << std::endl;
			}
			
		}
	}*/


	//	line(image, Point(10, 14),
		//	Point(29,13), Scalar(0, 0, 255), 3, 8);
	
		
	  

		return mask;

}
