#include "houghcircle.h"
#include "addcircle.h"

Mat Houghcircle::hough(Mat inimage, int rmin, int rmax)
{
	int rows = inimage.rows;
	int cols = inimage.cols;

	int nradii = rmax - rmin + 1;

	Mat h =Mat::zeros(rows,cols*nradii, CV_32SC1);

	Mat x ,y;



	for(int col=0;col<cols;col++)
	{
		for (int row = 0; row < rows; row++)
		{
			if (inimage.at<double>(row, col) != 0) 
			{
				x.push_back(col);
				y.push_back(row);
			}
		}
	}

	Addcircle addcircle;	

	for (int index = 0; index <y.rows; index++) 
	{
	
		int cx = x.at<int>(index);
		int cy = y.at<int>(index);


		
		for (int n = 0; n <nradii; n++) 
		{
			
		  Mat  ha = addcircle.addcircle( rows,cols,  cx,  cy, n+rmin+1, 1);
			
		  
		  Mat  bo = Mat::zeros(rows, cols, CV_32SC1);
			for (int i = 0; i< ha.rows; i++)
			{
				if (bo.at<int>(ha.at<int>(i, 0), ha.at<int>(i, 1)) == 0) 
				{
					bo.at<int>(ha.at<int>(i, 0), ha.at<int>(i, 1)) = bo.at<int>(ha.at<int>(i, 0), ha.at<int>(i, 1)) + 1;
					h.at<int>(ha.at<int>(i, 0), (n*cols + ha.at<int>(i, 1))) = h.at<int>(ha.at<int>(i, 0), (n*cols + ha.at<int>(i, 1)))+1;
				}
			}		

			//hf = hf + h;
		}
	}



	return h;

}

