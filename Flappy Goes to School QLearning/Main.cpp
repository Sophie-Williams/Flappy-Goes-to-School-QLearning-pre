#include <time.h>

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

string imagePath = "File\\Image\\";
string filePath = "File\\Text\\";
string QPath = "File\\Text\\QValue.txt";

int imageCounter;

StaticBot bot;
QLearning QBot(.7, 1.0);

vector<int> processTime, scores;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);
	QBot.readQValue(QPath);

	for (int i = 0; i < 5000; i++)
	{
		Sleep(3000);
		desktopIO.mouseClick(480, 560, 30);

		Mat image;
		bool alive = true;
		int distX, distY, scope, flappyHeight, preFlappyHeight=300;

		clock_t processStartTime, gameStartTime;

		Sleep(2000);

		for (int i = 0; i < 100; i++)
		{
			image = screen.getScreen(385, 35, 585, 500);
		}

		desktopIO.mouseClick(680, 440, 30);
		gameStartTime = clock();

		Sleep(500);

		while (1)
		{
			//processStartTime = clock();

			image = screen.getScreen(385, 35, 585, 500);
			alive = imageLib.extractFeature(image, distX, distY, scope, flappyHeight);

			//processTime.push_back(clock() - processStartTime);

			if (!alive)
			{
				break;
			}

			if (QBot.getAction(Helper::getState(distX, distY, scope, preFlappyHeight-flappyHeight)))
			{
				desktopIO.mouseClick(680, 440, 20);
			}

			preFlappyHeight = flappyHeight;
			QBot.addReward(1);

			/*circle(image, Point(5, flappyHeight), 3, Scalar(0, 0, 255), 2, 8);
			line(image, Point(distX + 5, flappyHeight + distY), Point(distX + 5 + 26,  flappyHeight + distY), Scalar(0, 255, 0), 2, 8);
			line(image, Point(distX + 5, flappyHeight + distY - 36), Point(distX + 5 + 26, flappyHeight + distY - 36), Scalar(0, 255, 0), 2, 8);
			line(image, Point(5, flappyHeight), Point(5, flappyHeight + scope), Scalar(255, 0, 0), 2, 8);

			FileIO::saveImage(image, imagePath, to_string(imageCounter++));*/
		}

		QBot.getAction("dead");
		QBot.addReward(-10);
		QBot.update();
		QBot.saveQValue(QPath);

		FileIO::saveValue((clock() - gameStartTime) / 1000, filePath, "Score.txt");
	}

	cin.ignore();
}