#pragma once
#pragma once
#include<iostream>
#include<time.h>
#include"canvas.h"
LRESULT CALLBACK unload(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
class tg_Frame
{
public:
	tg_Frame(LPCWSTR name, int width, int height, LPCWSTR class_name = L"test", decltype(unload) WinSunProc = unload);
	canvas* GetCanvas() { return &screen; }
	int* get_pixels() { return screen.getptr(); }
	int get_w() { return screen.get_w(); }
	int get_h() { return screen.get_h(); }
	int before_work();
	int after_work();
	HWND get_hwnd() { return hwnd; }
	~tg_Frame() {
		DestroyWindow(hwnd);
		UnregisterClass(wndcls.lpszClassName, wndcls.hInstance);
	};
private:
	WNDCLASS wndcls;
	HWND hwnd;
	canvas screen;
};


