#include "addcircle.h"



#include "canny.h"

Mat Addcircle::addcircle(int nrows, int ncols, int cx, int cy, int radius, int weight)
{

	Mat h = Mat::zeros(nrows, ncols, CV_32SC1);
	int hr = h.rows;
	int hc = h.cols;

	Mat x(1, floor(radius / sqrt(2)) + 1, CV_32SC1);
	Mat y(1, floor(radius / sqrt(2)) + 1, CV_32SC1);
	for (int i = 0; i <= floor(radius / sqrt(2)); i++)
	{
		x.at <int>(0, i) = i;
		double costheta = sqrt(1 - ((double(i*i)) / (double(radius*radius))));
		y.at <int>(0, i) = round(radius*costheta);
	}

	Mat px;
	hconcat(x, y, px);
	hconcat(px, y, px);
	hconcat(px, x, px);
	hconcat(px, -x, px);
	hconcat(px, -y, px);
	hconcat(px, -y, px);
	hconcat(px, -x, px);

	Mat py;
	hconcat(y, x, py);
	hconcat(py, -x, py);
	hconcat(py, -y, py);
	hconcat(py, -y, py);
	hconcat(py, -x, py);
	hconcat(py, x, py);
	hconcat(py, y, py);

	px = px + cy;
	py = py + cx;

	Mat validx;

	inRange(px, 0, nrows - 1, validx);
	validx = validx / 255;

	Mat validy;
	inRange(py, 0, ncols - 1, validy);
	validy = validy / 255;


	Mat	valid = validx.mul(validy);

	findNonZero(valid, valid);

	Mat validpy;
	Mat validpx;

	for (int i = 0; i < valid.rows; i++)
	{
		validpx.push_back(px.at<int>(valid.at<int>(i, 0)));
		validpy.push_back(py.at<int>(valid.at<int>(i, 0)));
	}

/*	for (int i = 0; i <validpx.rows; i++)
	{
		h.at<int>(validpx.at<int>(i), validpy.at<int>(i)) = weight;

	}*/

	hconcat(validpx,validpy,validpy);


	

	
	return validpy;


}





