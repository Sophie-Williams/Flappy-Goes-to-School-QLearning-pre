#pragma once

#include <windows.h>

#include "opencv2\opencv.hpp"

using namespace cv;

class Screen
{
public:
	Screen();
	~Screen();

	Mat getScreen(int x, int y, int height, int width);

private:
	Mat hwnd2mat(HWND hwnd, int x, int y, int h, int w);
};