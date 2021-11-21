#include "hysthresh.h"

Mat Hysthresh::hysthresh(Mat im, double T1, double T2)
{
	if (T2 > T1 || T2 < 0 || T1 < 0) 
	{
		std::cout << "error hysthresh line 6" << std::endl;
		exit(EXIT_FAILURE);
	
	}

	double rows = im.rows;
	double cols = im.cols;

	double rc = rows*cols;
	double rcmr = rc - rows;
	double rp1 = rows + 1;

	//std::cout << rc << std::endl;

	//Mat bw=Mat::zeros(rc, 1, CV_64F);
	Mat bw=Mat(rc, 1, CV_64FC1);
	
	transpose(im, im);
     bw = im.reshape(1,rc);
	//std::cout<<bw.rows<<std::endl;
	//std::cout << bw.cols << std::endl;

	 Mat pix;

	 for(int i=0;i<rc;i++)
	 {
		 if (bw.at<double>(i, 0) > T1) 
		 {
			 pix.push_back(i);
		 }
	 }

	 int npix = pix.rows;

	 Mat stack= Mat::zeros(rc, 1, CV_64F);

	 for(int i=0;i<npix;i++)
	 {
		 stack.at<double>(i, 0) =pix.at<int>(i,0);
	 }

	 int stp = npix;

	 for (int k = 0; k < npix; k++) 
	 {
		 bw.at<double>(pix.at<int>(k, 0), 0) = -1;
	 }

	Mat O =(Mat_<double>(1, 8) << -1, 1, -rows - 1, -rows, -rows + 1, rows - 1, rows, rows + 1);
	//std::cout << stp << std::endl;
	while(stp!=0)
	{
		double v = stack.at <double>(stp-1 , 0);
		//std::cout << v << std::endl;
		stp = stp - 1;
		if (v > rp1-1 && v < rcmr-1) 
		{
			Mat index = O + v;
			
			for (int i = 0; i <=7; i++) 
			{
				int ind = index.at<double>(0,i);
				
				if (bw.at<double>(ind,0)> T2)
				{
					stp = stp + 1;  
					stack.at<double>(stp-1,0) = ind;
					bw.at<double>(ind,0) = -1;
				}

			}
		}
	}

	for(int i=0;i<rc;i++)
	{
		if(bw.at<double>(i)!=-1)
		{
			bw.at<double>(i) = 0;
		}
		else 
		{
			bw.at<double>(i) = 1;
		}
	
	}

	bw = bw.reshape(1,cols);
	transpose(bw, bw);

	return bw;
	//imshow("gblur", bw);

}
