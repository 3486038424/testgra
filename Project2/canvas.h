#pragma once
#include<Windows.h>
#include<vector>
#include"tg_vec2d.h"
class canvas
{
	int w, h;
	HDC screenDC;
	HDC memDC;
	HBITMAP bitmap;
	BITMAPINFO info;
	int* ptr;
	HWND hwnd;
	tg_vec2d *line(float bx, float by, float ex, float ey,int& l_s);
public:
	int get_h() { return h-1; }
	int get_w() { return w-1; }
	int* getptr() { return ptr; }
	~canvas(){
		DeleteDC(memDC);
		DeleteObject(bitmap);
		ReleaseDC(NULL, screenDC);
	}
	int reset();
	int init(HWND hwnd);
	int draw();
	int tg_DrawLine(tg_vec2d begin, tg_vec2d end);
	int tg_fill(tg_vec2d* l1, tg_vec2d* l2, int& l1_s, int& l2_s);
	int tg_DrawRect(int b_x, int b_y, int e_x, int e_y);
	int tg_DrawTrangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3);
};

