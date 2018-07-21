/*#include "Screen.h"
#include "opencv2/opencv.hpp"
#include "FileIO.h"

using namespace std;
using namespace cv;
Screen screen;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	Sleep(3000);

	for (int i = 0; i < 100; i++)
	{
		Mat image = FileIO::getImage("File\\Image\\", to_string(i));
		
		imshow("Image", image);
		waitKey();
	}
}*/