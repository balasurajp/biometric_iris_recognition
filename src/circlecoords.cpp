#include "circlecoords.h"

void Circlecoords::circlecoords(int cr, int cc, int r, int imr, int imc, double nsides)
{
	nsides = round(nsides);


	Mat a(1, 2*nsides + 1, CV_64F);
	Mat xd(1, 2 * nsides + 1, CV_64F);
	Mat yd(1, 2 * nsides + 1, CV_64F);


	for (int i = 0; i <= 2*nsides; i++)
	{
		a.at <double>(i) = (( CV_PI) / nsides)*i;
		xd.at <double>(i) = round( double(r)*cos(a.at <double>(i)) + double(cr));
		yd.at <double>(i) = round(double(r)*sin(a.at <double>(i)) + double(cc));
	}



	for (int i = 0; i < xd.cols; i++) 
	{
		if (xd.at<double>(i) >= imr) 
		{
			std::cout << imr << std::endl;
			xd.at<double>(i) = imr - 1;
		}

		else if (xd.at<double>(i) < 0)
		{
			xd.at<double>(i) = 0;
		}

		if (yd.at<double>(i) >= imc)
		{
			std::cout << imc << std::endl;
			yd.at<double>(i) = imc - 1;
		}

		else if (yd.at<double>(i) < 0)
		{
			yd.at<double>(i) = 0;
		}


	}




	xd.convertTo(x, CV_32S);
	yd.convertTo(y, CV_32S);

	

}
