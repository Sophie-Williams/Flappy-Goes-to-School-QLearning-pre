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

int flappyHeight;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	for (int i = 0; i < 3; i++)
	{
		Sleep(3000);
		desktopIO.mouseClick(480, 560, 30);

		Mat image;
		bool alive = true;
		int flappyHeight;

		Sleep(2000);
		desktopIO.mouseClick(680, 440, 30);
		Sleep(500);

		while (1)
		{
			image = screen.getScreen(385, 35, 585, 500);
			alive = imageLib.extractFeature(image, flappyHeight);

			if (!alive)
			{
				break;
			}
		}
	}
}