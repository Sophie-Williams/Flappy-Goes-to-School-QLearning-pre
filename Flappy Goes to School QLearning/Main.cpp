#include <iostream>

#include "opencv2/opencv.hpp"
#include "Screen.h"

using namespace std;
using namespace cv;

Screen screen;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	Sleep(3000);

	Mat image = screen.getScreen(385, 35, 585, 500);
	imshow("Image", image);
	waitKey();
}