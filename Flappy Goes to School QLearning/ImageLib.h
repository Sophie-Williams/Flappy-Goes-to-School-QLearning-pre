#pragma once

#include "opencv2\opencv.hpp"
#include "FileIO.h"

using namespace std;
using namespace cv;

class ImageLib
{
public:
	ImageLib();
	~ImageLib();

	bool extractFeature(Mat image, int & distX, int & distY, int & scope, int &flappyHeight);

private:
	bool isAlive(Mat image, int &height);
	void getPillarPos(Mat image, int &x, int &y);
};