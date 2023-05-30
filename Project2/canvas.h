#pragma once
#include<Windows.h>
#include<vector>
class canvas
{
	int w, h;
	HDC screenDC;
	HDC memDC;
	HBITMAP bitmap;
	BITMAPINFO info;
	int* ptr;
	HWND hwnd;
	std::vector<int*> *line(float bx, float by, float ex, float ey);
public:
	int get_h() { return h-1; }
	int get_w() { return w-1; }
	int* getptr() { return ptr; }
	~canvas(){
		DeleteDC(memDC);
		DeleteObject(bitmap);
		ReleaseDC(NULL, screenDC);
	}
	int reset(int width,int height);
	int init(HWND hwnd, int width, int height);
	int draw();
	int tg_DrawLine(float b_x, float b_y, float e_x, float e_y);
	int tg_fill(std::vector<int*>* l1, std::vector<int*>* l2);
	int tg_DrawRect(int b_x, int b_y, int e_x, int e_y);
	int tg_DrawTrangle(int x1, int y1, int x2, int y2, int x3, int y3);
};

