#pragma once

#include <windows.h>

class DesktopIO
{
public:
	DesktopIO();
	~DesktopIO();

	void mouseClick(int x, int y, int sleep);

private:
	void leftClick(int sleep);
	void setMousePosition(POINT& mp);
};