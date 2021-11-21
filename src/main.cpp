
#include "segmentiris.h"
#include "normaliseiris.h"
#include "encode.h"




int main()
{
	clock_t begin = clock();


	int radial_res = 20;
	int angular_res = 240;


	int nscales = 1;
	int minWaveLength = 18;
	int mult = 1;// not applicable if using nscales = 1
	double sigmaOnf = 0.5;

	String name = "eye4.jpg";

	Mat eyeimage = imread(name, CV_LOAD_IMAGE_GRAYSCALE);


	Segmentiris segmentiris;
	segmentiris.segmentiris(eyeimage);

	Mat circleiris = segmentiris.circleiris;
	Mat circlepupil = segmentiris.circlepupil;
	Mat imagewithnoise = segmentiris.imagewithnoise;
	Mat imagewithcircles;

	/*FileStorage fs("test.yml", FileStorage::WRITE);
	fs << "mat" << imagewithnoise;
	fs.release();*/

	Mat modimagewithnoise;


	imagewithnoise.convertTo(modimagewithnoise, CV_8U);
	eyeimage.convertTo(imagewithcircles, CV_8U);
	
/*	Point centerI;
	centerI.x = circleiris.at<int>(1);
	centerI.y = circleiris.at<int>(0);*/

	Mat xcoordI = segmentiris.xcoordI;
	Mat ycoordI = segmentiris.ycoordI;

	for (int i = 0; i < xcoordI.cols; i++)
	{
		imagewithcircles.at<char>(xcoordI.at<int>(i), ycoordI.at<int>(i)) = 255;
	}


	for (int i = 0; i < xcoordI.cols; i++)
	{
		modimagewithnoise.at<char>(xcoordI.at<int>(i), ycoordI.at<int>(i)) = 255;
	}



	Point centerP;
	centerP.x = circlepupil.at<int>(1);
	centerP.y = circlepupil.at<int>(0);


	circle(imagewithcircles,
		centerP,
		circlepupil.at<int>(2),
		Scalar(255),
		1,
		8);

/*	circle(imagewithcircles,
		centerI,
		circleiris.at<int>(2),
		Scalar(255),
		1,
		8);*/

	circle(modimagewithnoise,
		centerP,
		circlepupil.at<int>(2),
		Scalar(255),
		1,
		8);

/*	circle(modimagewithnoise,
		centerI,
		circleiris.at<int>(2),
		Scalar(255),
		1,
		8);*/

	

	imwrite("diagnostics/"+name + "-noise.jpg", modimagewithnoise, {1,75});
	imwrite("diagnostics/"+name + "-segmented.jpg", imagewithcircles, { 1,75 });


	Normaliseiris normaliseiris;

	normaliseiris.normaliseiris(imagewithnoise, (circleiris.at<int>(1)+1), 
		(circleiris.at<int>(0)+1), circleiris.at<int>(2), (circlepupil.at<int>(1)+1), (circlepupil.at<int>(0)+1), circlepupil.at<int>(2),name, radial_res, angular_res);


	Mat polar_array = normaliseiris.polar_array;
	Mat noise_array = normaliseiris.polar_noise;

	imwrite("diagnostics/" + name + "-polar.jpg", polar_array, { 1,75 });
	imwrite("diagnostics/" + name + "-polarnoise.jpg", noise_array, { 1,75 });

	Encode encode;
	encode.encode(polar_array, noise_array, nscales, minWaveLength, mult, sigmaOnf);



	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


//	imshow("segmented Iris", polar_array);


	std::cout << elapsed_secs << std::endl;
//	std::cout << polar_array << std::endl;

	imshow("gblur", noise_array);
	waitKey();
	return 0;

	
}