#include "DesktopIO.h"



void DesktopIO::mouseClick(int x, int y, int sleep)
{
	POINT point;
	point.x = x;
	point.y = y;

	setMousePosition(point);
	leftClick(sleep);
}

DesktopIO::DesktopIO()
{
}


DesktopIO::~DesktopIO()
{
}


void DesktopIO::leftClick(int sleep)
{
	INPUT    Input = { 0 };												// Create our input.

	Input.type = INPUT_MOUSE;									        // Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;							// We are setting left mouse button down.
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.

	Sleep(sleep);

	ZeroMemory(&Input, sizeof(INPUT));									// Fills a block of memory with zeros.
	Input.type = INPUT_MOUSE;									        // Let input know we are using the mouse.
	Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;								// We are setting left mouse button up.
	SendInput(1, &Input, sizeof(INPUT));								// Send the input.
}

void DesktopIO::setMousePosition(POINT& mp)
{
	long fScreenWidth = GetSystemMetrics(SM_CXSCREEN) - 1;
	long fScreenHeight = GetSystemMetrics(SM_CYSCREEN) - 1;

	// http://msdn.microsoft.com/en-us/library/ms646260(VS.85).aspx
	// If MOUSEEVENTF_ABSOLUTE value is specified, dx and dy contain normalized absolute coordinates between 0 and 65,535.
	// The event procedure maps these coordinates onto the display surface.
	// Coordinate (0,0) maps onto the upper-left corner of the display surface, (65535,65535) maps onto the lower-right corner.
	float fx = mp.x * (65535.0f / fScreenWidth);
	float fy = mp.y * (65535.0f / fScreenHeight);

	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;

	Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;

	Input.mi.dx = (long)fx;
	Input.mi.dy = (long)fy;

	SendInput(1, &Input, sizeof(INPUT));
}