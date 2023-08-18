#include "canvas.h"
#include <iostream>
int canvas::init(HWND hwnd)
{
	frameCount = 0;
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
	ptr = (int*)malloc(width * height * 4);  // 4字节per像素
	z_ptr = (int*)malloc(width * height * 4);  // 4字节per像素
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
	z_ptr = (int*)malloc(width * height * 4);  // 4字节per像素
	return 0;
}
template<typename T>
void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
tg_vec2d* canvas::line(tg_vec2d begin, tg_vec2d end, int& l_s)
{
	l_s = 0;
	float d1 = 0, d2 = 0,  m = begin.far_2(end);
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
tg_vec3d* canvas::line_3(tg_vec3d begin, tg_vec3d end, int& l_s)
{
	if (begin.y > end.y)swap(begin, end);
	l_s = 0;
	float d1=0, d2=0, d3=0,m=begin.far_3(end);
	float k1 = (end.x - begin.x)/m, k2 = (end.y - begin.y)/m, k3 = (end.z - begin.z)/m;
	tg_vec3d u(begin);
	tg_vec3d* d = new tg_vec3d[m*3+10];
	d[l_s] = u;
	l_s++;
	while (!(u == end))
	{
		bool c = 0;
		d1 += k1; d2 += k2; d3 += k3;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1;}
		if (d3 <= -1) { u.z--; d3++; c = 1;}
		if (d1 >= 1) { u.x++; d1--; c = 1;}
		if (d2 >= 1) { u.y++; d2--; c = 1;}
		if (d3 >= 1) { u.z++; d3--; c = 1;}
		if (c) { d[l_s] = u; l_s++; }
	}
	return d;
}
int canvas::tg_DrawLine(tg_vec2d begin, tg_vec2d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	for (auto it = 0; it != l_s; it++)
	{
		ptr[int(d[it].x * w + d[it].y)] = RGB(255, 0, 0);
	}
	delete d;
	return 0;
}; 
int canvas::get_color(tg_vec3d& b, tg_vec3d& e, tg_vec2d& t,float z)
{
	tg_vec3d k(b);
	k.x += (e.x - b.x) * z;
	k.y += (e.y - b.y) * z;
	k.z += (e.z - b.z) * z;
	if (k.z<0||(z_ptr[int(t.x * w + t.y)] != -1 &&z_ptr[int(t.x * w + t.y)]<k.z ))return ptr[int(t.x * w + t.y)];
	z_ptr[int(t.x * w + t.y)] = k.z;
	return RGB(255, 0, 255-k.z);
}
int canvas::tg_DrawLine3d(tg_vec3d begin, tg_vec3d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	for (int it = 0; it != l_s; it++)
	{
		ptr[int(d[it].x * w + d[it].y)] = get_color(begin,end,d[it],it/(l_s*1.0));
	}
	if(l_s>1)delete d;
	return 0;
};
int canvas::tg_fill(tg_vec2d* l1, tg_vec2d* l2, int l1_s, int l2_s)
{
	if (l1[0].y > l2[0].y) { swap(l2, l1); swap(l1_s, l2_s); }
	int i = 0, j = 0;
	int t1 = 0, t2 = 0, offest, z;
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
			if (z == l1[i].y || z + 1 >= l2[j].y)
			ptr[offest+ z] = RGB(0, 0, 125);
		}
		do { i++; if (i == l1_s)return 0; } while (l1[i].x == l1[i - 1].x);
	}
	return 0;
};
int canvas::tg_fill_3(tg_vec3d* l1, tg_vec3d* l2, int l1_s, int l2_s)
{
	if (l1[0].y > l2[0].y) { swap(l2, l1); swap(l1_s, l2_s); }

	int i = 0, j = 0;
	int t1 = 0, t2 = 0, offest, z;
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
		std::cout << l1[i].x << ' ' << l2[i].x << ' ';
		std::cout << l1[i].y << ' ' << l2[i].y << ' ';
		std::cout << l1[i].z << ' ' << l2[i].z << '\n';

		tg_DrawLine3d(l1[i], l2[j]);
		do { i++; if (i == l1_s)return 0; } while (l1[i].x == l1[i - 1].x);
	}
	return 0;
};

int canvas::tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3)
{
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line(v1, v2,ls1);
	tg_vec2d* l2 = line(v3,v2,ls2);
	tg_vec2d* l3 = line(v1, v3,ls3);
	tg_fill(l1, l2,ls1,ls2); 
	tg_fill(l3, l2,ls3,ls2); 
	tg_fill(l1, l3,ls1,ls3);
	delete l1;
	delete l2;
	delete l3;
	return 0;
}
int canvas::tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3)
{
	/*
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec3d* l1 = line_3(v1, v2, ls1);
	tg_vec3d* l2 = line_3(v3, v2, ls2);
	tg_vec3d* l3 = line_3(v1, v3, ls3);
	tg_fill_3(l1, l2, ls1, ls2);
	tg_fill_3(l3, l2, ls3, ls2);
	tg_fill_3(l1, l3, ls1, ls3);
	delete l1;
	delete l2;
	delete l3;
	*/
	int ls = 0;
	tg_vec3d* l1 = line_3(v2, v3, ls);
	for (int i = 0; i < ls; i++)tg_DrawLine3d(l1[i], v1);
	return 0;
}