
#include "ImageLib.h"



ImageLib::ImageLib()
{
}


ImageLib::~ImageLib()
{
}

bool ImageLib::extractFeature(Mat image, int &flappyHeight)
{
	Rect roiFlappy(0, 0, 50, 550);
	Mat imageFlappy = image(roiFlappy);

	if (!isAlive(imageFlappy, flappyHeight))
	{
		return false;
	}

	int x, y;
	getPillarPos(image, x, y);

	circle(image, Point(25, flappyHeight), 15, Scalar(0, 0, 255), 2, 8);
	line(image, Point(x, y), Point(x + 130, y), Scalar(0, 255, 0), 2, 8);
	line(image, Point(x, y - 180), Point(x + 130, y - 180), Scalar(0, 255, 0), 2, 8);
	
	FileIO::saveImage(image, imagePath, to_string(imageCounter++));

	return true;
}

bool ImageLib::isAlive(Mat image, int & height)
{
	Mat mask;
	inRange(image, Scalar(0, 170, 200), Scalar(50, 185, 225), mask);

	for (int i = 0; i < mask.rows; i++)
	{
		for (int j = 0; j < mask.cols; j++)
		{
			if (mask.at<uchar>(i, j))
			{
				height = i;
				return true;
			}
		}
	}

	return false;
}

void ImageLib::getPillarPos(Mat image, int & x, int & y)
{
	Mat mask;
	inRange(image, Scalar(20, 105, 65), Scalar(80, 220, 160), mask);

	int kernel;
	Mat element;

	kernel = 5;
	element = getStructuringElement(MORPH_RECT, Size(2 * kernel + 1, 2 * kernel + 1), Point(kernel, kernel));
	morphologyEx(mask, mask, MORPH_CLOSE, element);

	kernel = 10;
	element = getStructuringElement(MORPH_RECT, Size(2 * kernel + 1, 2 * kernel + 1), Point(kernel, kernel));
	morphologyEx(mask, mask, MORPH_OPEN, element);

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	x = mask.cols;
	y = mask.rows / 2;

	for (int i = 0; i < contours.size(); i++)
	{
		int lowX = INT_MAX;
		int lowY = INT_MAX;
		int highX = INT_MIN;

		for (int j = 0; j < contours[i].size(); j++)
		{
			lowX = min(lowX, contours[i][j].x);
			lowY = min(lowY, contours[i][j].y);
			highX = max(highX, contours[i][j].x);
		}

		if (lowY == 0 || highX <= 5)
		{
			continue;
		}
		else if (x > lowX)
		{
			x = lowX;
			y = lowY;
		}
	}
}
