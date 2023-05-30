#include "canvas.h"
#include <iostream>
int canvas::init(HWND hwnd, int width, int height)
{
	this->hwnd = hwnd;
	screenDC = GetDC(hwnd);  
	memDC = CreateCompatibleDC(screenDC);
	w = width;                 // 宽度
	h = height;                // 高度
	bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memDC, bitmap, 0, height, NULL, &info, DIB_RGB_COLORS);
	ptr =(int *) malloc(width * height * 4);  // 4字节per像素
	return 0;
}
int canvas::draw()
{
	SetDIBits(memDC, bitmap, 0, h, ptr, &info, DIB_RGB_COLORS);
	BitBlt(screenDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
	return 0;
}
int canvas::reset(int width, int height)
{
	screenDC = GetDC(hwnd);  // 获取屏幕DC
	memDC = CreateCompatibleDC(screenDC);

	w = width;                 // 宽度
	h = height;                // 高度

	bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memDC, bitmap, 0, height, NULL, &info, DIB_RGB_COLORS);
	ptr =(int*) malloc(width * height * 4);  // 4字节per像素
	return 0;
}