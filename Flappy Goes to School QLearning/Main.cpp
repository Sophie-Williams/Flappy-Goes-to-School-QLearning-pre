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

QLearning QBot(.5, 1.0);

vector<int> processTime;

int main()
{
	ShowWindow(::GetConsoleWindow(), SW_MINIMIZE);

	cout << "Reading prevoius Q values" << endl;
	QBot.readQValue(QPath);

	for (int i = 0; i < 5000; i++)
	{
		cout << "iter: " << i + 1 << endl;
		Sleep(3000);
		desktopIO.mouseClick(480, 560, 30);

		Mat image;
		bool alive = true;
		int distX, distY, scope, flappyHeight, preFlappyHeight=40;

		clock_t processStartTime, gameStartTime;

		Sleep(2000);

		for (int j = 0; j < 50; j++)
		{
			image = screen.getScreen(385, 35, 585, 500);
			imageLib.extractFeature(image, distX, distY, scope, flappyHeight);
		}

		desktopIO.mouseClick(680, 440, 30);
		gameStartTime = clock();
		processTime.clear();

		Sleep(500);

		while (1)
		{
			processStartTime = clock();

			image = screen.getScreen(385, 35, 585, 500);
			alive = imageLib.extractFeature(image, distX, distY, scope, flappyHeight);

			processTime.push_back(clock() - processStartTime);

			if (!alive)
			{
				break;
			}

			if (QBot.getAction(Helper::getState(distX, distY, scope, preFlappyHeight-flappyHeight)))
			{
				desktopIO.mouseClick(680, 440, 30);
			}

			preFlappyHeight = flappyHeight;
			QBot.addReward(1);
		}

		QBot.getAction("dead");
		QBot.addReward(-100);
		QBot.update(distY >= 25, -100);
		QBot.saveQValue(QPath);

		FileIO::saveValue((clock() - gameStartTime) / 1000, filePath, "Score.txt");
		FileIO::saveValue(processTime, filePath, "Process Time.txt");

		cout << "Finished" << endl;
	}

	cin.ignore();
}