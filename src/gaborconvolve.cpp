#include "gaborconvolve.h"
#include "fft.h"

void Gaborconvolve::gaborconvolve(Mat image, int nscale, int minWaveLength, int mult, double sigmaOnf)
{

	int rows = image.rows;
	int cols = image.cols;

/*	FileStorage fs("test.yml", FileStorage::WRITE);
	fs << "mat" << image;
	fs.release(); */



//	Mat filtersum = Mat::zeros(1, cols , CV_64F);

//	Mat EO = cell(1, nscale);
	int ndata = cols;

	if (ndata % 2 == 1) 
	{
		ndata = ndata - 1;               
	}

	
	Mat logGabor = Mat::zeros(1, ndata,CV_64F);
//	Mat result  =  Mat::zeros(rows, ndata, CV_64F);

	Mat radius(1, (int(ndata / 2)+1), CV_64F);

	for(int i=0 ; i <= int(ndata / 2) ; i++)
	{
		radius.at<double>(i) = (double(i)/ int(ndata / 2))/2;
	}

	radius.at<double>(0) = 1;

	int wavelength = minWaveLength;

	double fo = 1.0 / double(wavelength);
	radius = radius / fo;
	log(radius, radius);
	pow(radius,2,radius);
	radius = radius/ (2 * (log(sigmaOnf)) *(log(sigmaOnf)));
	radius = -1 * radius;
	exp(radius, radius);

	for(int i=0; i < radius.cols ; i++)
	{
		
		logGabor.at<double>(i) = radius.at<double>(i);
	}

	logGabor.at<double>(0) = 0;

	Mat filter;
	Mat filtersum = Mat::zeros(logGabor.rows, logGabor.cols, CV_64F);

	Mat signal(1, image.cols, CV_64F);
	
	Mat imageifft;
	int nex = 0;

	Fft fft;
	fftw_complex x[N];
	// output array
	fftw_complex y[N];
	// fill the first array with some numbers

	Mat H1(image.rows, image.cols, CV_64F);
	Mat H2(image.rows, image.cols, CV_64F);

	Mat HMask1 = Mat::zeros(image.rows, image.cols, CV_64F);
	Mat HMask2 = Mat::zeros(image.rows, image.cols, CV_64F);


	for (int s = 0; s < nscale; s++) 
	{
		filter = logGabor;
		add(filter, filtersum, filtersum);

		for (int r = 0; r < rows; r++) 
		{
			nex = r + 1;
			signal = image(Range(r, nex), Range(0, image.cols));

			for (int i = 0; i < N; ++i)
			{
				x[i][REAL] = signal.at<double>(0,i);		// i.e., { 1, 2, 3, 4, 5, 6, 7, 8 }
				x[i][IMAG] = 0;
			}

			
		
			fft.fft(x, y);

		//	 fft.displayComplex(y);

			 std::cout << std::endl;
			 

			for (int i = 0; i < N; ++i)
			{
				y[i][REAL] = y[i][REAL]*filter.at<double>(i);		// i.e., { 1, 2, 3, 4, 5, 6, 7, 8 }
				y[i][IMAG] = y[i][IMAG]*filter.at<double>(i);
			}

			fft.ifft(y, x);

			for (int i = 0; i < N; ++i)
			{
				if (y[i][REAL] > 0) 
				{
					HMask1.at<double>(r, i) = 1.00;
				}

				if (y[i][IMAG] > 0)
				{
					HMask2.at<double>(r, i) = 1.00;
				}
				H1.at<double>(r,i) = y[i][REAL] ;		// i.e., { 1, 2, 3, 4, 5, 6, 7, 8 }
				H2.at<double>(r, i) = y[i][IMAG] ;
			}
	
		
		}

	}


	int split;

	split = filtersum.cols-int(filtersum.cols/2);

	Mat filtersum1;

	filtersum2 = filtersum(Range(0, 1), Range(split, filtersum.cols));
	filtersum1 = filtersum(Range(0, 1), Range(0, split));
	hconcat(filtersum2, filtersum1);


	


 /*   for(int i = 0 ; i < image.rows ;i++)
	{
		for (int j = 0; j < N; j++) 
		{
			H1.at<double>(i, j) = result[i][j][REAL];
			H2.at<double>(i, j) =  result[i][j][IMAG];
		}
	}*/

	H1r = H1;
	H2r = H2;
	

	Mat out = H1(Range(0, 20), Range(120, 240));
	
	std::cout << out << std::endl;
	imshow("segmented Iris", image);


}
