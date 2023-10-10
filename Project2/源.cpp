#pragma once
#include"tgra_win.h"
#include <time.h>
#include<iostream>
#include<random>
tgra_win* l;
//Image i("E://t.png");
int k = 0;
tg_vec2d* vecs;

void u()
{
	Graphics* gra=l->GetCanvas(0)->get_gra();
	for (int i = 0; i < 10; i++)
	{
		vecs[i].x += rand() / (float)RAND_MAX * 10 - 5;
		vecs[i].y += rand() / (float)RAND_MAX * 10;
		if (vecs[i].x < 0)vecs[i].x += 400;
		if (vecs[i].x > 400)vecs[i].x -= 400;
		if (vecs[i].y > 400)vecs[i].y -= 400;
	}
	for (int i = 0; i < 10; i++)
	{
		gra->tg_DrawCircle(vecs[i].x, vecs[i].y, 2);
	}
}

int main() {
	vecs = new tg_vec2d[10];
	for (int i = 0; i < 10; i++)
	{
		vecs[i] = tg_vec2d(rand()/ (float)RAND_MAX*400,0);
	}
	l = new tgra_win();
	l->new_tg_Frame(L"╣з0ап", 400, 400);
	l->insert(u);
	l->loop();
	return 0;
}
