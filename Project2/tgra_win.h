#pragma once
#include<Windows.h>
#include<iostream>
#include<time.h>
#include "works.h"
LRESULT CALLBACK unload(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
class tgra_win
{
public:
	tgra_win(LPCWSTR name, int width, int height, LPCWSTR class_name=L"test", decltype(unload) WinSunProc=unload);
	int loop();
	int* GetPixels() { return ((int*)ptr); }
	int get_w() { return w; }
	int get_h() { return h; }
	void insert(decltype(m) t) { work.add(t); }
	works work;
	WNDCLASS wndcls;
	HWND hwnd;
	int w, h;
	HDC screenDC;
	HDC memDC;
	RECT rc;
	HBITMAP bitmap;
	BITMAPINFO info;
	void* ptr;
};
