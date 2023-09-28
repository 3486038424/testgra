#pragma once
#include "Graphics.h"
class canvas
{
private:
	HDC screenDC;
	BITMAPINFO info;
	HWND hwnd;
	Graphics gra;
public:
	Graphics* get_gra() {
		return &gra;
	};
	bool set_pixel(int vec, int rgb);
	int get_h() { return gra.get_h(); }
	int get_w() { return gra.get_w(); }
	int* getptr() { return gra.getptr(); }
	~canvas() {
		ReleaseDC(NULL, screenDC);
	}
	int reset();
	int init(HWND hwnd);
	int draw();
	int clear()
	{
		return gra.clear();
	};
};

