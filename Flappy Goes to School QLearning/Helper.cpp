#include "Helper.h"



bool Helper::validMove(string state, int move)
{
	return true;
}

string Helper::getState(int distX, int distY, int scope, int speed)
{
	return to_string(distX) + '#' + to_string(distY) + '#' + to_string(scope) + '#' + to_string(speed);
}

Helper::Helper()
{
}


Helper::~Helper()
{
}
