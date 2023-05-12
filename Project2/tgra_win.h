
#pragma once
#include<Windows.h>
class tgra_win
{
public:
	tgra_win(LPCWSTR name, int width, int height);
	int loop();
private:
	WNDCLASS wndcls;
	HWND hwnd;
	int w, h;
	HDC screenDC;
	HDC memDC;
	RECT rc;
	HBITMAP bitmap;
	BITMAPINFO info;
	void* ptr;
};
