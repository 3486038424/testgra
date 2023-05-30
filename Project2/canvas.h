#pragma once
#include<Windows.h>
class canvas
{
	int w, h;
	HDC screenDC;
	HDC memDC;
	HBITMAP bitmap;
	BITMAPINFO info;
	int* ptr;
	HWND hwnd;
public:
	int get_h() { return h; }
	int get_w() { return w; }
	int* getptr() { return (int*) ptr; }
	int tg_DrawLine(int b_x, int b_y, int e_x, int e_y)
	{
		for (int i = b_x; i < e_x; i++)
		{
			int offset = i * w;
			for (int j = b_y; j < e_y; j++)
			{
				ptr[offset + j] = RGB(255, 0, 0);
			}
		}
		return 0;
	};
	~canvas(){
		DeleteDC(memDC);
		DeleteObject(bitmap);
		ReleaseDC(NULL, screenDC);
	}
	int reset(int w, int h);
	int init(HWND hwnd,int width,int height);
	int draw();
};

