#include "StaticBot.h"



StaticBot::StaticBot()
{
}


StaticBot::~StaticBot()
{
}

int StaticBot::getAction(int distX, int distY, int scope, int speed)
{

	if (distY <= -20 || (distY < 15 && speed <= 0) || speed < -25)
	{
		return 1;
	}
	return 0;
}
