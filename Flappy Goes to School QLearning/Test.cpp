/*#include <time.h>

#include "Screen.h"
#include "ImageLib.h"
#include "FileIO.h"
#include "DesktopIO.h"
#include "Helper.h"
#include "StaticBot.h"
#include "QLearning.h"

using namespace std;
using namespace cv;

Screen screen;
ImageLib imageLib;
DesktopIO desktopIO;

int imageCounter;

StaticBot bot;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	for (int i = 0; i < 5; i++)
	{
		Sleep(3000);
		desktopIO.mouseClick(480, 560, 25);

		Mat image;
		bool alive = true;
		int distX, distY, scope, flappyHeight, preFlappyHeight = 40;

		Sleep(2000);

		for (int j = 0; j < 50; j++)
		{
			image = screen.getScreen(385, 35, 585, 500);
			imageLib.extractFeature(image, distX, distY, scope, flappyHeight);
		}

		desktopIO.mouseClick(680, 440, 25);

		Sleep(500);

		while (1)
		{

			image = screen.getScreen(385, 35, 585, 500);
			alive = imageLib.extractFeature(image, distX, distY, scope, flappyHeight);

			if (!alive)
			{
				break;
			}

			if (bot.getAction(distX, distY, scope, preFlappyHeight - flappyHeight))
			{
				desktopIO.mouseClick(680, 440, 25);
			}

			preFlappyHeight = flappyHeight;
		}
	}

	cin.ignore();
}*/