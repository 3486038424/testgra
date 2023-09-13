#pragma once
#include "Graphics.h"
class canvas
{
private:
	HDC screenDC;
	HDC memDC;
	HBITMAP bitmap;
	BITMAPINFO info;
	HWND hwnd;
	Graphics gra;
public:
	bool set_pixel(int vec, int rgb);
	int get_h() { return gra.get_h(); }
	int get_w() { return gra.get_w(); }
	int* getptr() { return gra.getptr(); }
	void drawpic(Image img, int x, int y, int delta_x, int delta_y);
	~canvas() {
		DeleteDC(memDC);
		DeleteObject(bitmap);
		ReleaseDC(NULL, screenDC);
	}
	int reset();
	int init(HWND hwnd);
	int draw();
	int tg_DrawLine(tg_vec2d begin, tg_vec2d end);
	int tg_DrawLine3d(tg_vec3d begin, tg_vec3d end);
	int tg_DrawRect(int b_x, int b_y, int e_x, int e_y);
	int tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3);
	int tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3);
	int clear()
	{
		return gra.clear();
	};
};

