#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class StaticBot
{
public:
	StaticBot();
	~StaticBot();

	int getAction(int distX, int distY, int scope, int speed);
};