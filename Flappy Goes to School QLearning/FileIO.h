#pragma once

#include<string>

#include "opencv2/opencv.hpp"

using namespace std;
using namespace cv;

class FileIO
{
public:
	void static saveImage(Mat image, string path, string fileName);
	Mat static getImage(string path, string fileName);
	void static saveValue(int value, string path, string fileName);

private:
	FileIO();
	~FileIO();
};

