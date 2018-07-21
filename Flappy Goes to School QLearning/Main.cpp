#include "Screen.h"
#include "ImageLib.h"
#include "FileIO.h"

using namespace std;
using namespace cv;

Screen screen;
ImageLib imageLib;

string imagePath = "File\\Image\\";

int flappyHeight;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	//Sleep(5000);

	for (int i = 0; i < 100; i++)
	{
		Mat image = FileIO::getImage(imagePath, to_string(i));
		imageLib.extractFeature(image, flappyHeight);
	}
}