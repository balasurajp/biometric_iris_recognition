#include<iostream>
#include"opencv2\opencv.hpp"
#include"canny.h"

using namespace cv;

//class Cannyeye
//{

//public:

   

	void Cannyeye:: CannyreturnGradient(Mat im,double sigma,double scaling,double vert,double horz)
	{
	
		

		double xscaling = vert;
		double yscaling = horz;

		//gaussian kernal
		int ksize ;
		
		ksize = 6*sigma + 1;
		int ktype = CV_64F;//value store type
		Mat gkernel= GaussianKernel(ksize,sigma, ktype);// gaussian kernal

		Mat gblur;//image after applying gaussian filter

		Point anchor = Point(-1, -1);
		int borderType = BORDER_CONSTANT;//padding with zeros

		filter2D(im, gblur, -2, gkernel, anchor, 0, borderType);//funtion to apply any filter -2(negitive defaut)

		Mat scaledgblur;//the scaled image

		resize(gblur, scaledgblur, cvSize(0, 0), scaling, scaling);//resized gaussian blur
		//imwrite("Gray_Image.jpg", scaledgblur);

		int rows = scaledgblur.rows;
		int cols = scaledgblur.cols;

		Mat h = ReturnH(scaledgblur, rows, cols);
		Mat v = ReturnV(scaledgblur, rows, cols);
		Mat d1 = ReturnD1(scaledgblur, rows, cols);
		Mat d2 = ReturnD2(scaledgblur, rows, cols);

		Mat X, Y;

		X = (h + (d1 + d2) / 2)*xscaling;
		Y = (v + (d1 - d2) / 2)*yscaling;
		
		cartToPolar(X, Y, Gradient, or , true);
		Mat into = Mat::zeros(rows, cols, CV_64F);
		into.setTo(1, or > 180);
		or = or -(180*into);
		
	
	}

	
//private:
	  Mat Cannyeye::GaussianKernel(int ksize,double sigma,int ktype)
	  {
	  

		  Mat kernelX = getGaussianKernel(ksize, sigma, ktype);
		  Mat kernelY = getGaussianKernel(ksize, sigma, ktype);
		  Mat kernelXY = kernelX * kernelY.t();

		  return kernelXY;


	  }

	  Mat Cannyeye::ReturnH(Mat scaledgblur,int rows,int cols)
	  {
			
		  Mat A = scaledgblur(Range(0, rows), Range(1, cols));
		  hconcat(A, Mat::zeros(rows, 1, CV_64F) , A);
		  Mat B = scaledgblur(Range(0, rows), Range(0, cols-1));
		  hconcat(Mat::zeros(rows, 1, CV_64F), B, B);
		  A = A - B;
		  return A;

	  
	  }

	  Mat Cannyeye::ReturnV(Mat scaledgblur, int rows, int cols)
	  {

		  Mat zeroh = Mat::zeros(1, cols, CV_64F);
		  Mat C = scaledgblur(Range(1, rows), Range(0, cols));
		  C.push_back(zeroh);//add row
		  Mat D = scaledgblur(Range(0, rows-1), Range(0, cols));
		  zeroh.push_back(D);
		  D = zeroh;
		  C = C - D;

		  return C;

	  }

	  Mat Cannyeye::ReturnD1(Mat scaledgblur, int rows, int cols)
	  {
		  Mat zeroh = Mat::zeros(1, cols, CV_64F);
		  Mat E1 = scaledgblur(Range(1, rows), Range(1, cols));
		  hconcat(E1, Mat::zeros(rows-1, 1, CV_64F), E1);
		  E1.push_back(Mat::zeros(1, cols, CV_64F));

		  Mat E2 = scaledgblur(Range(0, rows-1), Range(0, cols-1));
		  hconcat(Mat::zeros(rows-1, 1, CV_64F), E2, E2);
		  zeroh.push_back(E2);
		  E2 = zeroh;

		  E1 = E1 - E2;

		  return E1;
	  }

	  Mat Cannyeye::ReturnD2(Mat scaledgblur,int rows, int cols)
	  {
		Mat zeroh = Mat::zeros(1, cols-1, CV_64F);
		Mat F1 = scaledgblur(Range(0, rows-1), Range(1, cols));
		zeroh.push_back(F1);
		F1 = zeroh;
		hconcat(F1, Mat::zeros(rows, 1, CV_64F), F1);
		zeroh = Mat::zeros(1, cols, CV_64F);

		Mat F2 = scaledgblur(Range(1, rows), Range(0, cols-1));
		hconcat(Mat::zeros(rows-1, 1, CV_64F), F2, F2);
		F2.push_back(Mat::zeros(1, cols, CV_64F));

		F1 = F1 - F2;

		return F1;
	  
	  }

	 
//};





