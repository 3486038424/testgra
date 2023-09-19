#pragma once
#include<iostream>
#include<time.h>
#include"canvas.h"
#include "works.h"
LRESULT CALLBACK unload(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
class tgra_win
{
public:
	tgra_win(LPCWSTR name, int width, int height, LPCWSTR class_name=L"test", decltype(unload) WinSunProc=unload);
	int loop();
	canvas* GetCanvas() { return &screen; }
	int* get_pixels() { return screen.getptr(); }
	int get_w() { return screen.get_w(); }
	int get_h() { return screen.get_h(); }
	void insert(decltype(m) t) { work.add(t); }
	int one_loop();
private:
	works work;
	WNDCLASS wndcls;
	HWND hwnd;
	canvas screen;
};
