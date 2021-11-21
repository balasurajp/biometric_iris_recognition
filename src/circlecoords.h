#ifndef CIRCLECOORDS_H
#define CIRCLECOORDS_H

#include<iostream>
#include"opencv2\opencv.hpp"
using namespace cv;


class Circlecoords
{
public:
	Mat x, y;
	void circlecoords(int cr, int cc, int r, int imr, int imc, double nsides);
};

#endif;
