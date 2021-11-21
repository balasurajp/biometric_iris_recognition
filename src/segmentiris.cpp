 #include "segmentiris.h"
#include "circlecoords.h"

void Segmentiris::segmentiris(Mat eyeimage)
{

	

	int lpupilradius = 28;
	int upupilradius = 75;
	int lirisradius = 80;
	int uirisradius = 150;

	float scaling = 0.4;
	int reflecthres = 240;

	
	eyeimage.convertTo(eyeimage, CV_64FC1);
	Findcircle findcircle;
	circleiris = findcircle.findcircle(eyeimage, lirisradius, uirisradius, scaling, 2, 0.20, 0.19, 1.00, 0.00);


	double rowd = double(circleiris.at<int>(0) + 1);
	double cold = double(circleiris.at<int>(1) + 1);
	double rd = double(circleiris.at<int>(2) + 1);

	int irl = round(rowd - rd);
	int iru = round(rowd + rd);
	int icl = round(cold - rd);
	int icu = round(cold + rd);

	int rows = eyeimage.rows;
	int cols = eyeimage.cols;

	if (irl < 1)
	{
		irl = 1;
	}

	if (icl < 1)
	{
		icl = 1;

	}
	if (iru > rows)
	{
		iru = rows;
	}

	if (icu > cols)
	{
		icu = cols;
	}

	Mat imagepupil = eyeimage(Range(irl - 1, iru), Range(icl - 1, icu));



	 circlepupil = findcircle.findcircle(imagepupil, lpupilradius, upupilradius, 0.6, 2, 0.25, 0.25, 1.00, 1.00);



	double rowp = double(circlepupil.at<int>(0));
	double colp = double(circlepupil.at<int>(1));
	double r = double(circlepupil.at<int>(2));

	double row = double(irl) + rowp;
	double col = double(icl) + colp;

	row = round(row);
	col = round(col);

	circlepupil.at<int>(0) = row;
	circlepupil.at<int>(1) = col;
	circlepupil.at<int>(2) = r;

   
	eyeimage.convertTo(imagewithnoise, CV_64F);

	Mat topeyelid = imagepupil(Range(0, (rowp - r)), Range(0, imagepupil.cols));

	Findline findline;
	Mat lineT = findline.findline(topeyelid);

	
	

	Mat bottomeyelid = imagepupil(Range(rowp + r + 1, imagepupil.rows), Range(0, imagepupil.cols));
	Mat lineB = findline.findline(bottomeyelid);

	Mat linenoisetemplate;
	vconcat(lineT, Mat::zeros(2 * r, imagepupil.cols, CV_32S), linenoisetemplate);
	vconcat(linenoisetemplate, lineB, linenoisetemplate);
	vconcat(Mat::zeros(irl - 1, imagepupil.cols, CV_32S), linenoisetemplate, linenoisetemplate);
	vconcat(linenoisetemplate, Mat::zeros((eyeimage.rows - iru + 1), imagepupil.cols, CV_32S), linenoisetemplate);
	hconcat(Mat::zeros(eyeimage.rows, (icl - 1), CV_32S), linenoisetemplate, linenoisetemplate);
	hconcat(linenoisetemplate, Mat::zeros(eyeimage.rows, eyeimage.cols - icu, CV_32S), linenoisetemplate);

	Mat circlenoisetemplate = Mat::zeros(eyeimage.rows, eyeimage.cols, CV_32S);


/*	Point centerI;
	centerI.x = circleiris.at<int>(1);
	centerI.y = circleiris.at<int>(0);

	
	circle(circlenoisetemplate,
		centerI,
		circleiris.at<int>(2),
		Scalar(1),
		-1,
		8);*/

	Circlecoords circlecoords;

	circlecoords.circlecoords(circleiris.at<int>(0), circleiris.at<int>(1), circleiris.at<int>(2), eyeimage.rows, eyeimage.cols, 600);

	 xcoordI = circlecoords.x;
	 ycoordI = circlecoords.y;

	for (int i = 0; i < xcoordI.cols; i++)
	{
		circlenoisetemplate.at<int>(xcoordI.at<int>(i), ycoordI.at<int>(i)) = 1;
	}


	

	circlenoisetemplate = circlenoisetemplate.mul(linenoisetemplate);

	int topLim = rowd - rd - 1;
	int botLim = rowd + rd + 1;

	for (int i = 0; i < circlenoisetemplate.rows; i++)
	{
		for (int j = 0; j<circlenoisetemplate.cols; j++)
		{
			if (i >= 0 && i <= (row - r - 1))
			{
				if (circlenoisetemplate.at<int>(i, j) == 1)
				{
					topLim = i;
				}

			}

			if (i >= (row + r + 1))
			{
				if ((circlenoisetemplate.at<int>(i, j) == 1) && i<botLim)
				{
					botLim = i;

				}

			}

		}
	}

	for (int i = 0; i <= topLim; i++)
	{
		for (int j = icl - 1; j < icu; j++)
		{
			imagewithnoise.at<double>(i, j) = NAN;
		}
	}


	for (int i = botLim; i < eyeimage.rows; i++)
	{
		for (int j = icl - 1; j < icu; j++)
		{
			imagewithnoise.at<double>(i, j) = NAN;
		}
	}

	eyeimage.convertTo(eyeimage, CV_64FC1);

	

	for (int i = 0; i < eyeimage.rows; i++)
	{
		for (int j = 0; j < eyeimage.cols; j++)
		{
			if (eyeimage.at<double>(i, j) < 100)
			{
				imagewithnoise.at<double>(i, j) = NAN;
			}
		}
	}

}
