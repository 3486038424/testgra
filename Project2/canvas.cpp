#include "canvas.h"
#include <iostream>
bool canvas::set_pixel(int vec, int rgb)
{
	return gra.set_pixel(vec,rgb);
}
void canvas::drawpic(Image img, int x, int y, int delta_x, int delta_y)
{
	gra.drawpic(img, x, y, delta_x, delta_y);
}
int canvas::init(HWND hwnd)
{
	int width, height;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	width = clientRect.right;
	height = clientRect.bottom;
	this->hwnd = hwnd;
	screenDC = GetDC(hwnd);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	gra.init(width, height);
	return 0;
}
int canvas::draw()
{
	SetDIBitsToDevice(screenDC, 0, 0, gra.get_h()+1, gra.get_h()+1, 0, 0, 0, gra.get_h()+1, 
		gra.getptr(), &info, DIB_RGB_COLORS);
	return 0;
}
int canvas::reset()
{
	int width, height;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	width = clientRect.right;
	height = clientRect.bottom;
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	return gra.reset(width,height);
}
int canvas::tg_DrawLine(tg_vec2d begin, tg_vec2d end)
{
	return gra.tg_DrawLine(begin,end);
};

int canvas::tg_DrawLine3d(tg_vec3d begin, tg_vec3d end)
{
	return tg_DrawLine3d(begin, end);
};
int canvas::tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3)
{
	return tg_DrawTriangle(v1, v2, v3);
}
int canvas::tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3)
{
	return tg_DrawTriangle_3d(v1, v2, v3);
}

