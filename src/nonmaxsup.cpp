#include"nonmaxsup.h"

Mat Nonmaxsup::nonmaxup(Mat inimage, Mat orient, double radius)
{
	if (inimage.rows != orient.rows || inimage.cols != orient.cols)
	{
		std::cout << "error nonmaxsup line 6" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (radius < 1)
	{
		std::cout << "error nonmaxsup line 11" << std::endl;
		exit(EXIT_FAILURE);
	}

	int rows = inimage.rows;
	int cols = inimage.cols;

	Mat im = Mat::zeros(rows, cols, CV_64F);

	int iradius = ceil(radius);


	Mat angle = Mat::zeros(1, 181, CV_64F);

	for (int i = 0; i <= 180; i++)
	{
		angle.at<double>(0, i) = i;

	}

	double pi = CV_PI;

	angle = angle * CV_PI / 180;

	Mat xoff = Mat::zeros(1, 181, CV_64F);

	for (int i = 0; i <= 180; i++)
	{
		xoff.at<double>(0, i) = radius*cos(angle.at<double>(0, i));
	}

	Mat yoff = Mat::zeros(1, 181, CV_64F);

	for (int i = 0; i <= 180; i++)
	{
		yoff.at<double>(0, i) = radius*sin(angle.at<double>(0, i));
	}

	Mat hfrac = Mat::zeros(1, 181, CV_64F);

	for (int i = 0; i <= 180; i++)
	{
		hfrac.at<double>(0, i) = xoff.at<double>(0, i) - floor(xoff.at<double>(0, i));
	}

	Mat vfrac = Mat::zeros(1, 181, CV_64F);

	for (int i = 0; i <= 180; i++)
	{
		vfrac.at<double>(0, i) = yoff.at<double>(0, i) - floor(yoff.at<double>(0, i));
	}

	//orient = orient + 1.0;  not needed because the matrix start from zero

	for (int row = iradius; row <= rows - iradius - 1; row++)
	{
		for (int col = iradius; col <= cols - iradius - 1; col++)
		{
			double or = orient.at<double>(row, col);
			double x = col + xoff.at<double>(0, int(or )) + 1;
			double y = row - yoff.at<double>(0, int(or )) + 1;

			double fx = floor(x);
			double cx = ceil(x);
			double fy = floor(y);
			double cy = ceil(y);

			double tl = inimage.at<double>(fy - 1, fx - 1);
			double tr = inimage.at<double>(fy - 1, cx - 1);
			double bl = inimage.at<double>(cy - 1, fx - 1);
			double br = inimage.at<double>(cy - 1, cx - 1);

			double upperavg = tl + hfrac.at<double>(0, int(or )) * (tr - tl);
			double loweravg = bl + hfrac.at<double>(0, int(or )) * (br - bl);

			double v1 = upperavg + vfrac.at<double>(0, int(or )) * (loweravg - upperavg);

			if (inimage.at<double>(row, col)>v1)
			{
				x = col - xoff.at<double>(0, int(or )) + 1;
				y = row + yoff.at<double>(0, int(or )) + 1;

				fx = floor(x);
				cx = ceil(x);
				fy = floor(y);
				cy = ceil(y);

				tl = inimage.at<double>(fy - 1, fx - 1);
				tr = inimage.at<double>(fy - 1, cx - 1);
				bl = inimage.at<double>(cy - 1, fx - 1);
				br = inimage.at<double>(cy - 1, cx - 1);

				upperavg = tl + hfrac.at<double>(0, int(or )) * (tr - tl);
				loweravg = bl + hfrac.at<double>(0, int(or )) * (br - bl);

				double v2 = upperavg + vfrac.at<double>(0, int(or )) * (loweravg - upperavg);

				if (inimage.at<double>(row, col) > v2)
				{
					im.at<double>(row, col) = inimage.at<double>(row, col);

				}



			}

		}
	}

	return im;
}
