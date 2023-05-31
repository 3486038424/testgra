#include "canvas.h"
#include <iostream>
int canvas::init(HWND hwnd)
{
	int width, height;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	width = clientRect.right;
	height = clientRect.bottom;
	this->hwnd = hwnd;
	screenDC = GetDC(hwnd);  
	memDC = CreateCompatibleDC(screenDC);
	w = width;                 // 宽度
	h = height;                // 高度
	bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memDC, bitmap, width, height, NULL, &info, DIB_RGB_COLORS);
	ptr =(int *) malloc(width * height * 4);  // 4字节per像素
	return 0;
}
int canvas::draw()
{
	SetDIBits(memDC, bitmap, 0, h, ptr, &info, DIB_RGB_COLORS);
	BitBlt(screenDC, 0, 0, w, h, memDC, 0, 0, SRCCOPY);
	return 0;
}
int canvas::reset()
{
	int width,height;
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);
	width = clientRect.right;
	height = clientRect.bottom;
	screenDC = GetDC(hwnd);  // 获取屏幕DC
	memDC = CreateCompatibleDC(screenDC);
	w = width;                 // 宽度
	h = height;                // 高度
	bitmap = CreateCompatibleBitmap(screenDC, width, height);
	SelectObject(memDC, bitmap);
	info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	info.bmiHeader.biWidth = width;
	info.bmiHeader.biHeight = height;
	info.bmiHeader.biPlanes = 1;
	info.bmiHeader.biBitCount = 32;  // 使用32位像素格式
	info.bmiHeader.biCompression = BI_RGB;
	GetDIBits(memDC, bitmap, width, height, NULL, &info, DIB_RGB_COLORS);
	ptr =(int*) malloc(width * height * 4);  // 4字节per像素
	return 0;
}

void swap(float& a, float& b)
{
	float c = a;
	a = b;
	b = c;
}
void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}
tg_vec2d* canvas::line(float bx, float by, float ex, float ey,int &l_s)
{
	if (bx == ex) {
		tg_vec2d* d = new tg_vec2d[ey-by+5];
		int dt = ey - by > 0 ? 1 : -1;
		while (by < ey)
		{
			by += dt;
			d[l_s].x = bx;
			d[l_s].y = by;
			l_s++;
		}
		return d;
	}
	if (bx > ex) { swap(bx, ex); swap(by, ey); }
	//std::cout << bx << ' ' << ex << std::endl;

	float delta = (ey - by) / (1.0 * (ex - bx)),dy=by;
	int c = 0;
	if (delta < 0) { c = -1; }
	else if (delta > 0) { c = 1; }
	tg_vec2d* d = new tg_vec2d[w + h+5];
	float a1, a2, a3;
	int bby = by;
	while (1)
	{
		a1 = (bby + c) - dy;
		a2 = (bby)-dy - delta;
		a3 = (bby + c) - dy - delta;
		if (a1 < 0)a1 = -a1;
		if (a2 < 0)a2 = -a2;
		if (a3 < 0)a3 = -a3;
		if (a1 < a2)
		{
			if(a1<a3){
				bby+=c;
			}
			else {
				bby+=c;
				bx++;
				dy += delta;
			}
		}
		else {
			if (a2 < a3) { bx++;dy += delta;}
			else { bx++; bby+=c;dy += delta;}
		}
		if (bx > ex)break;
		d[l_s].x=bx;
		d[l_s].y = bby;
		l_s++;
	}

	return d;
	
}

int canvas::tg_DrawLine(tg_vec2d begin, tg_vec2d end)
{
	int l_s=0;
	tg_vec2d* d = line(begin.x, begin.y, end.x, end.y,l_s);
	for (auto it = 0; it != l_s; it++)
	{
		ptr[int(d[it].x * w + d[it].y)] = RGB(255, 0, 0);
	}
	delete d;
	return 0;
}; 
int canvas::tg_fill(tg_vec2d* l1, tg_vec2d* l2,int &l1_s,int &l2_s)
{
	if (l1[0].y > l2[0].y) { auto l3 = l1; l1 = l2; l2 = l3; swap(l1_s, l2_s); }
	int i = 0, j = 0;
	int t1 = 0,t2=0,offest, z;
	while (l1[i].x < l2[j].x)
	{
		i++; if (i == l1_s)return 0;
	}
	while (1)
	{
		while (l1[i].x > l2[j].x)
		{
			j++; if (j == l2_s)return 0;
		}
		offest = l1[i].x * w;
		for (z = l1[i].y; z < l2[j].y; z++) {
			ptr[offest+ z] = RGB(0, 0, 125);
		}
		do { i++; if (i == l1_s)return 0; } while (l1[i].x == l1[i - 1].x);
	}
	return 0;
};

int canvas::tg_DrawTrangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3)
{
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line(v1.x, v1.y, v2.x, v2.y,ls1);
	tg_vec2d* l2 = line(v3.x, v3.y, v2.x, v2.y,ls2);
	tg_vec2d* l3 = line(v1.x, v1.y, v3.x, v3.y,ls3);
	tg_fill(l1, l2,ls1,ls2); 
	tg_fill(l3, l2,ls3,ls2); 
	tg_fill(l1, l3,ls1,ls3);
	delete l1;
	delete l2;
	delete l3;
	return 0;
}