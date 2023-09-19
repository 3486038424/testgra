#pragma once
#include<Windows.h>
#include<vector>
#include"tg_vec2d.h"
#include "Image.h"

template<typename T>
void swap(T& a, T& b);
class Graphics
{
public:
	int w, h;
	int frameCount;
	int* ptr;
	int* z_ptr;
	int k;
	int len;
	tg_vec2d* line(tg_vec2d begin, tg_vec2d end, int& l_s);
	bool get_color_2(tg_vec2d& b, tg_vec2d& e, int z, int offset);
	bool set_pixel(int vec, int rgb);
	int get_h() { return h - 1; }
	int get_w() { return w - 1; }
	int* getptr() { return ptr; }
	void drawpic(Image img, int x, int y, int delta_x, int delta_y);
	int reset(int width,int height);
	int init(int width,int height);
	int tg_DrawLine(tg_vec2d begin, tg_vec2d end);
	int tg_DrawLine3d(tg_vec3d begin, tg_vec3d end);
	tg_vec3d* line_3(tg_vec3d begin, tg_vec3d end, int& l_s);
	int tg_fill(tg_vec2d* l1, tg_vec2d* l2, int l1_s, int l2_s);
	int tg_DrawRect(int b_x, int b_y, int e_x, int e_y);
	int tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3);
	int tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3);
	bool get_color(tg_vec3d& b, tg_vec3d& e, tg_vec2d& t, float z, int& rgb);
	int tg_DrawTriangle_3d_with_image(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3, Image&img, tg_vec2d vc1, tg_vec2d vc2, tg_vec2d vc3);
	int clear()
	{
		k = 0;
		frameCount++;
		for (int i = 0; i < h * w; i++) { ptr[(i)] = RGB(255, 255, 255); z_ptr[i] = -1; }
		return 0;
	};
};

