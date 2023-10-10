#include "Graphics.h"
#include <iostream>
#include <cmath>
bool Graphics::set_pixel(int x, int y, int rgb)
{
	if (x<=0 || x>=w || y<=0 || y>=h)return false;
	ptr[y * w + x] = rgb;
	return true;
}
bool Graphics::set_pixel(int vec, int rgb)
{
	if (vec<0||vec>len)return false;
	ptr[vec] = rgb;
	return true;
}

int Graphics::tg_DrawRect(int b_x, int b_y, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for(int j=0;j<width;j++)set_pixel(b_x+j,b_y+i, RGB(0, 0, 0));
	}
	return 0;
}

int Graphics::tg_DrawCircle(int x, int y, int r)
{
	int bx=r, by=0;
	set_pixel(x + r, y , RGB(0, 0, 0));
	set_pixel(x - r, y , RGB(0, 0, 0));
	set_pixel(x + r, y , RGB(0, 0, 0));
	set_pixel(x + r, y , RGB(0, 0, 0));
	for (int i = x - r; i < x + r; i++)
	{
		set_pixel(i, y , RGB(0, 0, 0));
	}
	r = r * r;
	while (bx > by)
	{
		int r1 = (bx - 1) * (bx - 1) + (by + 1) * (by + 1);
		int r2 = (bx) * (bx)+(by + 1) * (by + 1);
		r1 -= r; if (r1 < 0)r1 = -r1;
		r2 -= r; if (r2 < 0)r2 = -r2;
		by++;
		if (r1<=r2)bx--;
		set_pixel(x + bx, y + by, RGB(0, 0, 0));
		set_pixel(x + bx, y - by, RGB(0, 0, 0));
		set_pixel(x - bx, y + by, RGB(0, 0, 0));
		set_pixel(x - bx, y - by, RGB(0, 0, 0));
		set_pixel(x + by, y + bx, RGB(0, 0, 0));
		set_pixel(x + by, y - bx, RGB(0, 0, 0));
		set_pixel(x - by, y + bx, RGB(0, 0, 0));
		set_pixel(x - by, y - bx, RGB(0, 0, 0)); 
		for (int i = x - bx; i < x + bx; i++)
		{
			set_pixel(i, y + by, RGB(0, 0, 0));
			set_pixel(i, y - by, RGB(0, 0, 0));
		}
		for (int i = x - by; i < x + by; i++)
		{
			set_pixel(i, y + bx, RGB(0, 0, 0));
			set_pixel(i, y - bx, RGB(0, 0, 0));
		}
	}
	return 0;
}

void Graphics::drawpic(Image img, int x, int y, int delta_x, int delta_y)
{
	int offset = (h - x + 1) * w;
	int z = x > 0 ? 0 : -x;
	for (int i = y > 0 ? 0 : -y; i < delta_y && i + y < h; i++)
	{
		offset -= w;
		if (offset<0 || offset>len)continue;
		int kt = img.height * i / delta_y * img.width;
		for (int j = z; j < delta_x && j + x < w; j++)
		{
			set_pixel(offset + j + y, img.get_color(kt + (y + j) * img.width / delta_x));
		}
	}
}
int Graphics::init(int width,int height)
{
	frameCount = 0;
	return reset(width,height);
}
int Graphics::reset(int width,int height)
{
	w = width;                 // 宽度
	h = height;                // 高度
	len = w * h;
	p = ptr;
	z = z_ptr;
	ptr = (int*)malloc(len * 4);  // 4字节per像素
	z_ptr = (int*)malloc(len * 4);  // 4字节per像素
	return 0;
}
template<typename T>
void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
tg_vec2d* Graphics::line(tg_vec2d begin, tg_vec2d end, int& l_s)
{
	l_s = 0;
	float d1 = 0, d2 = 0, m = begin.far_2(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m;
	tg_vec2d u(begin);
	tg_vec2d* d = new tg_vec2d[m * 3];
	d[l_s] = u;
	l_s++;
	while (!(u == end))
	{
		bool c = 0;
		d1 += k1; d2 += k2;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (d2 >= 1) { u.y++; d2--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	return d;
}

int Graphics::tg_DrawLine(tg_vec2d begin, tg_vec2d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	for (auto it = 0; it != l_s; it++)
	{
		set_pixel(int(d[it].x * w + d[it].y), RGB(255, 0, 0));
	}
	delete d;
	return 0;
};

int Graphics::tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3)
{
	if (v1.y < v2.y) { swap(v1, v2); }
	if (v2.y < v3.y) { swap(v2, v3); if (v1.y < v2.y) { swap(v1, v2); }}
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line(v1, v2, ls1);
	tg_vec2d* l2 = line(v2, v3, ls2);
	tg_vec2d* l3 = line(v1, v3, ls3);
	int len3 = 0, len1 = 0;
	float d = v3.x + (v1.x - v3.x) * (v2.y - v3.y) / (v1.y - v3.y);
	if (d < v2.x)d = 1; else d = -1;
	while (len3 != ls3)
	{
		int offset = l3[len3].y * w;
		for (int i = l3[len3].x; i != l1[len1].x; i+=d)set_pixel(offset + i, RGB(0, 0, 0));
		len3++;
		while (l3[len3 - 1].y == l3[len3].y)len3++;
		while (len1 < ls1 && l3[len3].y != l1[len1].y)len1++;
		if (len1 == ls1)
		{
			swap(l1, l2);
			swap(ls1, ls2);
			len1 = 0;
			while (len1 < ls1 && l3[len3].y != l1[len1].y)len1++;
		}
	}
	delete l1;
	delete l2;
	delete l3;
	return 0;
}

int Graphics::tg_DrawPolygon(tg_vec2d* buffer, int len)
{
	if (len < 3)return 1;
	for (int i = 0; i < len; i++)
	{
		tg_DrawTriangle(buffer[i], buffer[(i + 1) % len], buffer[(i + 2) % len]);
	}
	return 0;
}