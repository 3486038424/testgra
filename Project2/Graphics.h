#pragma once
#include<Windows.h>
#include"tg_vec2d.h"
#include "Image.h"
#define RGBA(r,g,b,a)  ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16))|(((DWORD)(BYTE)(a))<<24))
class Buffer
{
	tg_vec2d* buffer;
	int len;
	int index;
	void longer()
	{
		tg_vec2d* b = new tg_vec2d[len + 10];
		for (int i = 0; i < index; i++)b[i] = buffer[i];
		buffer = b;
		len += 20;
	}
public:
	Buffer(int length = 10) :len(length),index(0) { buffer = new tg_vec2d[length]; }
	int insert(tg_vec2d point)
	{
		if (index >= len) {
			longer();
		}
		buffer[index] = point;
		index++;
		return 0;
	}
	tg_vec2d* get_buffer() { return buffer; }
	int get_size() { return index; }
	tg_vec2d get(int in) { if (in<0||in >= index)return NULL; return buffer[in]; }
	int set(int in, tg_vec2d point) { if (in < 0 || in >= index)return 1; buffer[in] = point; return 0; }
};
template<typename T>
void swap(T& a, T& b);
void mix_color(int& color, int& goal);
class Graphics
{
	int w, h;
	int framecount;
	int* ptr = NULL;
	int* p = NULL;
	int k;
	int len;
	int fill_rgb=RGB(0,0,0,0);
	tg_vec2d* line(tg_vec2d begin, tg_vec2d end, int& l_s);
	bool set(int x, int y);
	bool set(int vec);
	bool set_pixel(int x, int y, int rgb);
	bool set_pixel(int vec, int rgb);
public:
	int frameCount() { return framecount; }
	int fill(int rgb) { fill_rgb = rgb; return 0; }
	void delete_zp() {  delete p; p = NULL; }
	int get_h() { return h - 1; }
	int get_w() { return w - 1; }
	int* getptr() { return ptr; }
	void drawpic(Image img, int x, int y, int delta_x, int delta_y);
	int tg_DrawCircle(int x, int y, int r);
	int reset(int width,int height);
	int init(int width,int height);
	int tg_DrawLine(tg_vec2d begin, tg_vec2d end);
	int tg_DrawRect(int b_x, int b_y, int width, int height);
	int tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3);
	int tg_DrawPolygon(Buffer buffer) { return tg_DrawPolygon(buffer.get_buffer(), buffer.get_size()); };
	int tg_DrawPolygon(tg_vec2d* buffer, int len);
	int background(int rgb)
	{
		for (int i = 0; i < len; i++) { mix_color(rgb, ptr[i]); }
		return 0;
	}
	int clear()
	{
		k = 0;
		framecount++;
		if (p != NULL)delete_zp();
		return 0;
	};
};

