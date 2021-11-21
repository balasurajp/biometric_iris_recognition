#include "encode.h"
#include "gaborconvolve.h"

void Encode::encode(Mat polar_array, Mat noise_array, int nscales, int minWaveLength, int mult, double sigmaOnf)
{

	Gaborconvolve gaborconvolve;
	gaborconvolve.gaborconvolve(polar_array,  nscales,  minWaveLength,  mult,  sigmaOnf);

	Mat H1 = gaborconvolve.H1r;
	Mat H2 = gaborconvolve.H2r;

	Mat flitertsum = gaborconvolve.filtersum2;

	int lenght = (polar_array.cols) * 2 * nscales;

	Mat temp = Mat::zeros(polar_array.rows, lenght ,CV_64F);

	int lenght2 = polar_array.cols;

/*	Mat h(1, polar_array.rows,CV_64F);   // = 1:size(polar_array, 1);

	for (int i = 0; i < polar_array.rows; i++) 
	{
		h.at<double>(i) = i + 1;
	
	}*/

	Mat mask = Mat::zeros(temp.rows,temp.cols,CV_64F);

	Mat H3(H1.rows, H1.cols, CV_64F);

	Mat waste;

	cartToPolar(H1, H2, H3, waste,true);

	Mat mask1 = Mat:: zeros(H1.rows, H1.cols, CV_64F);// = (H1 > 0);
	Mat mask2 = Mat::zeros(H1.rows, H1.cols, CV_64F);// = (H2 > 0);
	Mat mask3 = Mat::zeros(H1.rows, H1.cols, CV_64F);// = (H1 < 0.0001);

	for (int i = 0; i < H1.rows; i++) 
	{
		for (int j = 0; j < H1.cols; j++)
		{
			if(H1.at<double>(i,j) > 0)
			{
				mask1.at<double>(i, j) = 1;
			}

			if (H2.at<double>(i, j) > 0)
			{
				mask2.at<double>(i, j) = 1;
			}

			if (H3.at<double>(i, j) < 0.0001)
			{
				mask3.at<double>(i, j) = 1;
			}
		}
	
	}

	for (int h = 0; h < polar_array.rows; h++)
	{
		for (int i = 0; i < lenght2-1; i++)
		{
			double ja = double(2 * nscales*(i));
			//cout << ja + 1 << endl;

			if (mask1.at<double>(h, i ) == 1)
			{
				temp.at<double>(h, ja ) = 1.00;
			}


			if (mask2.at<double>(h, i ) == 1) 
			{
			
				temp.at<double>(h, ja + 1 ) = 1.00;
			}

			if (noise_array.at<double>(h, i ) == 1 || mask3.at<double>(h, i ) == 1)
			{
				mask.at<double>(h, ja) = 1.00;
			}

			if (noise_array.at<double>(h, i) == 1 || mask3.at<double>(h, i ) == 1)
			{
				mask.at<double>(h, ja + 1) = 1.00;
			}



		}


	
	
	
	}
		
	imshow("mask", mask);
	imshow("temp", temp);

}
