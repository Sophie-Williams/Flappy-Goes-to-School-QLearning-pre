
#include "ImageLib.h"



ImageLib::ImageLib()
{
}


ImageLib::~ImageLib()
{
}

bool ImageLib::extractFeature(Mat image, int & distX, int & distY, int & scope, int &flappyHeight)
{
	Rect roiFlappy(0, 0, 10, 110);
	Mat imageFlappy = image(roiFlappy);

	if (!isAlive(imageFlappy, flappyHeight))
	{
		return false;
	}

	int x, y;
	getPillarPos(image, x, y);

	distX = max(0, x - 5);
	distY = y - flappyHeight;
	scope = image.rows - flappyHeight;

	if (distX == 0)
	{
		scope = distY;
	}

	return true;
}

bool ImageLib::isAlive(Mat image, int & height)
{
	Mat mask;
	inRange(image, Scalar(0, 170, 200, 0), Scalar(50, 185, 225, 255), mask);

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
	inRange(image, Scalar(20, 105, 65, 0), Scalar(80, 220, 160, 255), mask);

	int kernel;
	Mat element;

	kernel = 1;
	element = getStructuringElement(MORPH_RECT, Size(2 * kernel + 1, 2 * kernel + 1), Point(kernel, kernel));
	morphologyEx(mask, mask, MORPH_CLOSE, element);

	kernel = 2;
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

		if (lowY == 0 || highX <= 10)
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
