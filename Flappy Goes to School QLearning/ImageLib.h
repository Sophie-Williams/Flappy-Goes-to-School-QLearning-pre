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

	bool extractFeature(Mat image, int &flappyHeight);

private:
	int imageCounter = 0;
	string imagePath = "File\\Image Edit\\";

	bool isAlive(Mat image, int &height);
	void getPillarPos(Mat image, int &x, int &y);
};