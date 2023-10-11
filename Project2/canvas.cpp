#include "canvas.h"
#include <iostream>
int canvas::init(HWND hwnd)
{
	int width, height;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	width = clientRect.right;
	height = clientRect.bottom;
	this->hwnd = hwnd;
	screenDC = GetDC(hwnd);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	gra.init(width, height);
	return 0;
}
int canvas::draw()
{
	SetDIBitsToDevice(screenDC, 0, 0,gra.get_w() + 1, gra.get_h() + 1, 0, 0,0 , gra.get_h() + 1,gra.getptr(), &info, DIB_RGB_COLORS);
	return 0;
}
int canvas::reset()
{
	int width, height;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	width = clientRect.right;
	height = clientRect.bottom;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	return gra.reset(width,height);
}


