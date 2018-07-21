#pragma once

#include <string>

using namespace std;

class Helper
{
public:
	static bool validMove(string state, int move);
	static string getState(int distX, int distY, int scope, int speed);
private:
	Helper();
	~Helper();
};

