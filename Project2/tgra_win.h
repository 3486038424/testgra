#pragma once
#include<iostream>
#include<time.h>
#include<vector>
#include "tg_font.h"
#include "tg_Frame.h"
#include "works.h"
class tgra_win
{
public:
	int new_tg_Frame(LPCWSTR name, int width, int height, LPCWSTR class_name = L"test", decltype(unload) WinSunProc = unload)
	{
		frame.push_back(new tg_Frame(name, width, height, class_name, WinSunProc));
		return 0;
	};
	int loop();
	canvas* GetCanvas(int i) 
	{ if (i<0 || i>=frame.size())return NULL; return frame[i]->GetCanvas(); }
	int* get_pixels(int i)
	{ if (i<0 || i>=frame.size())return NULL; return frame[i]->get_pixels(); }
	int get_w(int i) 
	{ if (i<0 || i>=frame.size())return 0; return frame[i]->get_w(); }
	int get_h(int i) 
	{ if (i<0 || i>=frame.size())return 0; return frame[i]->get_h(); }
	void insert(decltype(m) t) { work.add(t); }
	int one_loop();
	bool frameRate(int rate) { framerate = 1000 / rate; return true; }
	tg_Frame* get_Frame(int index) {
		if (index < 0 || index >= frame.size())return NULL; return frame[index];
	}
	std::bitset<256> keystate;
private:
	works work;
	double framerate=0;
	std::vector<tg_Frame*> frame;
};
