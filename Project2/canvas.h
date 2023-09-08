#pragma once
#include<Windows.h>
#include<vector>
#include"tg_vec2d.h"
template<typename T>
void swap(T& a, T& b);
class canvas
{
private:
	int w, h;
	HDC screenDC;
	HDC memDC;
	HBITMAP bitmap;
	BITMAPINFO info;
	int frameCount;
	int* ptr;
	int* z_ptr;
	HWND hwnd;
	int k;
	tg_vec2d* line(tg_vec2d begin, tg_vec2d end, int& l_s);
	tg_vec2d* line_2(tg_vec2d begin, tg_vec2d end, int& l_s);
	bool get_color_2(tg_vec2d& b, tg_vec2d& e, int z, int offset);
public:
	int get_h() { return h - 1; }
	int get_w() { return w - 1; }
	int* getptr() { return ptr; }
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
	tg_vec3d* line_3(tg_vec3d begin, tg_vec3d end, int& l_s);
	int tg_fill(tg_vec2d* l1, tg_vec2d* l2, int l1_s, int l2_s);
	int tg_DrawRect(int b_x, int b_y, int e_x, int e_y);
	int tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3);
	int tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3);
	int tg_fill_3(tg_vec3d* l1, tg_vec3d* l2, int l1_s, int l2_s);
	bool get_color(tg_vec3d& b, tg_vec3d& e, tg_vec2d& t, float z, int& rgb);
	int clear()
	{
		k = 0;
		frameCount++;
		for (int i = 0; i < h * w; i++) { ptr[(i)] = RGB(255, 255, 255); z_ptr[i] = -1; }
		return 0;
	};
};

