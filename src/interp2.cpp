#include "interp2.h"

Mat Interp2::interp2(Mat image, Mat X1, Mat Y1)
{
	Mat ret=Mat::ones(X1.rows, X1.cols, CV_64F);
	ret = -2 * ret;

	if (X1.rows != Y1.rows || Y1.cols != X1.cols) 
	{
		exit;
	}

	int xcoo;
	int ycoo;
	double r;
	double z3;
	double z1;
	double z2;
	double z4;

	Mat mask = Mat(image != image);

	mask = mask / 255;
	

	for (int i = 0; i < X1.rows; i++) 
	{
		for (int j = 0; j <X1.cols; j++) 
		{
			if (X1.at<double>(i, j) < 0 || X1.at<double>(i, j) > (image.cols-1) || Y1.at<double>(i, j) < 0 || Y1.at<double>(i, j) > (image.rows-1)) 
			{
				ret.at<double>(i,j) = NAN;
				
			}

		else 
			{

				xcoo = X1.at<double>(i, j);
				ycoo = Y1.at<double>(i, j);

				if ((X1.at<double>(i, j)- xcoo)==0 || (Y1.at<double>(i, j) - ycoo)==0)
				{

				

					if ((X1.at<double>(i, j) - xcoo) == 0 && (Y1.at<double>(i, j) - ycoo) == 0) 
					{
						

						if (mask.at<char>(ycoo, xcoo) == 1) 
						{
							ret.at<double>(i, j) = NAN;
							
						}
						else
						{
							ret.at<double>(i, j) = image.at<double>(ycoo, xcoo);
							
						}
					}

					else if ((X1.at<double>(i, j) - xcoo) == 0 && (Y1.at<double>(i, j) - ycoo) != 0)
					{
						
						if (mask.at<char>(ycoo, xcoo) == 1 || mask.at<char>(ycoo + 1, xcoo) == 1)
						{
							ret.at<double>(i, j) = NAN;
							
						}
						else 
						{
							ret.at<double>(i, j) = image.at<double>(ycoo, xcoo)*(1 - Y1.at<double>(i, j) + ycoo) + image.at<double>(ycoo + 1, xcoo)*(Y1.at<double>(i, j) - ycoo);
							
						}
					}

					else if ((X1.at<double>(i, j) - xcoo) != 0 && (Y1.at<double>(i, j) - ycoo) == 0)
					{
						
						if (mask.at<char>(ycoo, xcoo) == 1 || mask.at<char>(ycoo, xcoo+1) == 1)
						{
							
							ret.at<double>(i, j) = NAN;
							
						}
						else
						{
							
							
							ret.at<double>(i, j) = image.at<double>(ycoo, xcoo)*(1 - X1.at<double>(i, j) + xcoo) + image.at<double>(ycoo, xcoo + 1)*(X1.at<double>(i, j) - xcoo);
							
						}
					}

				}

				else {
				
					if ((Y1.at<double>(i, j) - ycoo) <= (1 - (X1.at<double>(i, j) - xcoo)))
					{
						z1 = image.at<double>(ycoo, xcoo);
						z2 = image.at<double>(ycoo, xcoo + 1);
						z3 = image.at<double>(ycoo + 1, xcoo);

						if (mask.at<char>(ycoo, xcoo) == 1 || mask.at<char>(ycoo + 1, xcoo + 1) == 1 || mask.at<char>(ycoo, xcoo + 1) == 1 || mask.at<char>(ycoo + 1, xcoo)== 1)
						{
							ret.at<double>(i, j) = NAN;
							
						}

						else
						{

							r = (z2 - z1)*xcoo + (z3 - z1)*ycoo - z1;
							ret.at<double>(i, j) = (z2 - z1)*((X1.at<double>(i, j))) + (z3 - z1)*(Y1.at<double>(i, j)) - r;
							
						}
					}
					else
					{
						z2 = image.at<double>(ycoo, xcoo + 1);
						z3 = image.at<double>(ycoo + 1, xcoo);
						z4 = image.at<double>(ycoo + 1, xcoo + 1);

						if (mask.at<char>(ycoo, xcoo) == 1 || mask.at<char>(ycoo + 1, xcoo + 1) == 1 || mask.at<char>(ycoo, xcoo + 1) == 1 || mask.at<char>(ycoo + 1, xcoo) == 1)
						{
							ret.at<double>(i, j) = NAN;
						}

						else
						{

							r = (z4 - z3)*(xcoo + 1) + (z4 - z2)*(ycoo + 1) - z4;
							ret.at<double>(i, j) = (z4 - z3)*(X1.at<double>(i, j)) + (z4 - z2)*(Y1.at<double>(i, j)) - r;
						}
					}
				}
			}
		
		}
	
	}

	
	//std::cout << mask.rows <<" "<< mask.cols << std::endl;

	return ret;
}
