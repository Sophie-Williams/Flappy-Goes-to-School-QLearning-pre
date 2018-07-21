#include "Screen.h"
#include "ImageLib.h"
#include "FileIO.h"
#include "DesktopIO.h"

using namespace std;
using namespace cv;

Screen screen;
ImageLib imageLib;
DesktopIO desktopIO;

string imagePath = "File\\Image\\";

int imageCounter;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	for (int i = 0; i < 1; i++)
	{
		Sleep(3000);
		desktopIO.mouseClick(480, 560, 30);

		Mat image;
		bool alive = true;
		int distX, distY, scope, flappyHeight, preFlappyHeight;

		Sleep(2000);
		desktopIO.mouseClick(680, 440, 30);
		Sleep(500);

		while (1)
		{
			image = screen.getScreen(385, 35, 585, 500);
			alive = imageLib.extractFeature(image, distX, distY, scope, flappyHeight);

			if (!alive)
			{
				break;
			}

			circle(image, Point(25, flappyHeight), 15, Scalar(0, 0, 255), 2, 8);
			line(image, Point(distX + 25, flappyHeight + distY), Point(distX + 25 + 130,  flappyHeight + distY), Scalar(0, 255, 0), 2, 8);
			line(image, Point(distX + 25, flappyHeight + distY - 180), Point(distX + 25 + 130, flappyHeight + distY -180), Scalar(0, 255, 0), 2, 8);
			line(image, Point(25, flappyHeight), Point(25, flappyHeight + scope), Scalar(255, 0, 0), 2, 8);

			FileIO::saveImage(image, imagePath, to_string(imageCounter++));
		}
	}
}