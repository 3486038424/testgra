#include "canvas.h"
#include <iostream>
int canvas::init(HWND hwnd,int width,int height)
{

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
int canvas::reset(int width,int height)
{
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

int canvas::tg_DrawRect(int b_x, int b_y, int e_x, int e_y)
{
	for (int i = b_x; i < e_x; i++)
	{
		int offset = i * w;
		for (int j = b_y; j < e_y; j++)
		{
			ptr[offset + j] = RGB(255, 0, 0);
		}
	}
	return 0;
}; 
void swap(float& a,float& b)
{
	float c = a;
	a = b; 
	b = c;
}
std::vector<int*>* canvas::line(float bx, float by, float ex, float ey)
{
	/*
	float delta = (ey - by) / (1.0 * (ex - bx));
	std::vector<int*>* d = new std::vector<int*>;
	while (bx <= ex)
	{
		int* a = new int[2];
		a[0] = bx;
		a[1] = by;
		bx++;
		by += delta;
		d->push_back(a);
	}
	return d;
	*/
	if (bx == ex) {
		std::vector<int*>* d = new std::vector<int*>;
		int dt = ey - by > 0 ? 1 : -1;
		while (by < ey)
		{
			int* a = new int[2];
			a[0] = bx;
			a[1] = by;
			by += dt;
			d->push_back(a);
		}
		return d;
	}
	if (bx > ex) { swap(bx, ex); swap(by, ey); }
	//std::cout << bx << ' ' << ex << std::endl;

	float delta = (ey - by) / (1.0 * (ex - bx)),dy=by;
	int c = 0;
	if (delta < 0) { c = -1; }
	else if (delta > 0) { c = 1; }
	std::vector<int*>* d = new std::vector<int*>;
	float a1, a2, a3;
	int bby = by;
	while (1)
	{
		int* a = new int[2];
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
		a[0] = bx;
		a[1] = bby;
		if (a[0] > ex)break;
		d->push_back(a);
	}

	return d;
	
}
int canvas::tg_DrawLine(float b_x, float b_y, float e_x, float e_y)
{
	std::vector<int*>* d = line(b_x, b_y, e_x, e_y);
	for (auto it = d->begin(); it != d->end(); it++)
	{
		ptr[(*it)[0] * w + (*it)[1]] = RGB(255, 0, 0);
	}
	return 0;
}; 
int canvas::tg_fill(std::vector<int*>* l1, std::vector<int*>* l2)
{
	int a = (*l1)[0][1];
	int b = (*l2)[0][1];
	if ((*l1)[0][1] > (*l2)[0][1]) { std::vector<int*>* l3 = l1; l1 = l2; l2 = l3; }
	int i = 0, j = 0;

	while (i < l1->size() && j < l2->size())
	{
		while ((*l1)[i][0] < (*l2)[j][0])
		{
			i++; if (i == l1->size())return 0;
		}
		while ((*l1)[i][0] > (*l2)[j][0])
		{
			j++; if (j == l2->size())return 0;
		}
		for (int z = (*l1)[i][1]; z < (*l2)[j][1]; z++) {
			ptr[(*l1)[i][0] * w + z] = RGB(0, 0, 125);
		}
		do { i++; if (i == l1->size())return 0; } while ((*l1)[i][0] == (*l1)[i - 1][0]);
	}
	return 0;
};

int canvas::tg_DrawTrangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
	int t = clock();
	std::vector<int*>* l1 = line(x1, y1, x2, y2);
	std::vector<int*>* l2 = line(x3, y3, x2, y2);
	std::vector<int*>* l3 = line(x1, y1, x3, y3);
	std::cout << clock() - t << std::endl;
	t = clock();
	tg_fill(l1, l2); 
	tg_fill(l3, l2); 
	tg_fill(l1, l3);

	std::cout << clock() - t << std::endl;
	return 0;
}