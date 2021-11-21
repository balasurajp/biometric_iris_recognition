#include "normaliseiris.h"
#include "interp2.h"
#include "circlecoords.h"
#include "segmentiris.h"

void Normaliseiris::normaliseiris(Mat image, int x_iris, int y_iris, int r_iris, int x_pupil, int y_pupil, int r_pupil, String eyeimage_filename, int radpixels, int angulardiv)
{
	
	int radiuspixels = radpixels + 2;
	int angledivisions = angulardiv - 1;

	Mat r(1, radiuspixels, CV_32SC1);
	for (int i = 0; i < radiuspixels; i++)
	{
		r.at <int>(0, i) = i;
	}

	Mat theta(1,  angledivisions+1, CV_64F);

	

	for (int i = 0; i <=angledivisions ;i++)
	{
		theta.at <double>(i) = ((2*CV_PI)/ angledivisions)*i;
	}


	x_iris = double(x_iris);
	y_iris = double(y_iris);
	r_iris = double(r_iris);

	x_pupil = double(x_pupil);
	y_pupil = double(y_pupil);
	r_pupil = double(r_pupil);

	double ox = x_pupil - x_iris;
	double oy = y_pupil - y_iris;

	int sgn;

	if (ox <= 0) 
	{
		sgn = -1;
	}
	else if(ox > 0)
	{
		sgn = 1;
	}


	if (ox == 0 && oy > 0)
	{
		sgn = 1;
	}

	r.convertTo(r,CV_64F);
	

	Mat a = Mat::ones(1, angledivisions + 1,CV_64F)* (ox*ox + oy*oy);

	double phi;
	if (ox == 0) 
	{
		 phi = CV_PI / 2;
	}
	else
	{
		phi = atan(oy / ox);
	}

	Mat b(1, theta.cols, CV_64F);
	for (int i = 0; i <theta.cols; i++) 
	{
		b.at<double>(i) = sgn*(cos(CV_PI - phi - theta.at<double>(i)));
	}

	Mat asto;
	Mat bsto;

	sqrt(a, asto);
	//pow(b, 2, bsto);
	bsto = a.mul(b.mul(b)) - (a - ((r_iris ) *(r_iris )));
	sqrt(bsto, bsto);
	r = ((b.mul(asto)) + (bsto));

	r = r - r_pupil;

	Mat rmat = Mat::ones(radiuspixels, 1,CV_64F)*r;

	Mat multinrmat(1, radiuspixels, CV_64F);

	for (int i = 0; i < radiuspixels; i++) 
	{
		multinrmat.at<double>(i) = i*(double(1) / double(radiuspixels - 1));
	}

	multinrmat = (Mat::ones(angledivisions + 1, 1, CV_64F))*(multinrmat);
	transpose(multinrmat, multinrmat);
	rmat = rmat.mul(multinrmat);

	
		rmat = rmat + r_pupil;

		rmat = rmat(Range(1, radiuspixels - 1), Range(0, rmat.cols));

		Mat thetacosmat(1,theta.cols,CV_64F);
		
		for (int i = 0; i < theta.cols; i++) 
		{
			thetacosmat.at<double>(i) = cos(theta.at<double>(i));
		}

		Mat thetasinmat(1, theta.cols, CV_64F);

		for (int i = 0; i < theta.cols; i++)
		{
			thetasinmat.at<double>(i) = sin(theta.at<double>(i));
		}

		Mat xcosmat = Mat::ones(radiuspixels - 2, 1, CV_64F)*thetacosmat;
		Mat xsinmat = Mat::ones(radiuspixels - 2, 1,CV_64F)*thetasinmat;

		Mat xo = rmat.mul(xcosmat);
		Mat yo = rmat.mul(xsinmat);



		xo = x_pupil + xo;
		yo = y_pupil - yo;


		Mat rx (1, image.cols, CV_64F);
		for (int i = 0; i < image.cols; i++) 
		{
			rx.at<double>(i) = i+1;
		}

		Mat x(image.rows,image.cols, CV_64F);

		repeat(rx, image.rows,1, x);


		Mat ry( image.rows, 1, CV_64F);
		for (int i = 0; i < image.rows; i++)
		{
			ry.at<double>(i) = i + 1;
		}

		Mat y(image.rows, image.cols, CV_64F);

		repeat(ry, 1, image.cols, y);

		 polar_array;// (image.rows, image.cols, CV_64F);

		xo.convertTo(xo, CV_64F);
		yo.convertTo(yo, CV_64F);


		Interp2 interp2;

		polar_array=interp2.interp2(image, xo-1, yo-1);

		 polar_noise = Mat::zeros(polar_array.rows, polar_array.cols, CV_64F);

		 Mat mask = Mat(polar_array != polar_array);
		 mask = mask / 255;

		for (int i=0; i < polar_array.rows; i++) 
		{
			for (int j=0; j < polar_array.cols; j++) 
			{
				if (mask.at<char>(i, j) == 1) 
				{
					polar_noise.at<double>(i, j) = 1;
				}
			}
		
		}

		polar_array = polar_array / 255;

		
		for (int i = 0; i < xo.rows; i++)
		{
			for (int j = 0; j < xo.cols; j++) {

				

				if (xo.at<double>(i,j)>image.cols)
				{
					xo.at<double>(i, j) = image.cols;
				}

				else if (xo.at<double>(i, j)<1)
				{
					xo.at<double>(i, j) = 1;
				}

			   if (yo.at<double>(i, j)>image.rows)
			   {
				  yo.at<double>(i, j) = image.rows;
		       }

			 else if (yo.at<double>(i, j)<1)
			  {
				yo.at<double>(i, j) = 1;
			  }

			   xo.at<double>(i, j) = round(xo.at<double>(i, j));
			   yo.at<double>(i, j) = round(yo.at<double>(i, j));
			

			}
		}

		image.convertTo(image, CV_8U);

		for(int i=0;i<xo.rows;i++)
		{
			for(int j=0;j<xo.cols;j++)
			{
				image.at<char>( (yo.at<double>(i, j)-1), (xo.at<double>(i, j)-1)) = 255;
			
			}
		
		}

/*		Point centerI;
		centerI.x = x_iris-1;
		centerI.y = y_iris-1;

		Point centerP;
		centerP.x = x_pupil-1;
		centerP.y = y_pupil-1;


		circle(image,
			centerP,
			r_iris,
			Scalar(255),
			1,
			8);

		circle(image,
			centerI,
			r_pupil,
			Scalar(255),
			1,
			8);*/


		Circlecoords circlecoords;
		circlecoords.circlecoords(y_iris - 1, x_iris - 1,r_iris,image.rows,image.cols,600);

		Mat xcoord = circlecoords.x;
		Mat ycoord = circlecoords.y;

		for (int i = 0; i < xcoord.cols; i++) 
		{
			image.at<char>(xcoord.at<int>(i), ycoord.at<int>(i)) = 255;
		
		}

		circlecoords.circlecoords(y_pupil - 1, x_pupil - 1, r_pupil, image.rows, image.cols, 600);

		 xcoord = circlecoords.x;
		 ycoord = circlecoords.y;

		for (int i = 0; i < xcoord.cols; i++)
		{
			image.at<char>(int(xcoord.at<int>(i)), int(ycoord.at<int>(i))) = 255;

		}


		imwrite("diagnostics/" + eyeimage_filename + "-normal.jpg", image, { 1,75 });

		Mat polar_array2;

		

		polar_array.copyTo(polar_array2);

	

		for (int i = 0; i < polar_array2.rows; i++) 
		{
			for (int j=0 ; j < polar_array2.cols ; j++)
			{
				if (mask.at<char>(i, j) == 1) 
				{
					

					polar_array2.at<double>(i, j) = 0.5;
				}
			
			}
		}

		double avg = (sum(polar_array2)[0])/(polar_array.rows*polar_array.cols);

		for (int i = 0; i < polar_array.rows; i++)
		{
			for (int j = 0; j < polar_array.cols; j++)
			{
				if (mask.at<char>(i, j) == 1)
				{
					polar_array.at<double>(i, j) = avg;
				}

			}
		}



//	std::cout << xcoord.cols <<" "<< oy<< std::endl;
//	std::cout << image << std::endl;
	

	


		
}
