#pragma once
#include"tgra_win.h"
#include <time.h>
#include<iostream>
tgra_win* l;
Image i("C://10.png");
int k = 0;
Buffer b;

#include<random>
tg_vec2d* vecs;

void u()
{
	Graphics gra=l->GetCanvas()->get_gra();
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
		gra.tg_DrawCircle(vecs[i].x, vecs[i].y, 2);
	}
}

int main() {
	vecs = new tg_vec2d[10];
	for (int i = 0; i < 10; i++)
	{
		vecs[i] = tg_vec2d(rand()/ (float)RAND_MAX*400,0);
	}
	l = new tgra_win(L"第0列", 400, 400);
	l->insert(u);
	l->one_loop();
	l->loop();
	return 0;
}

//问题之一，目前事件链依旧存在仅可以使用void空函数，需要进行修改，考虑增加抽象类控制。
//除去抽象类以外，考虑增加数值传入，不算合适，但可以。抽象类作为传参指针，进入函数后手动变换指针。(考虑到高版本的c++学习成本，慎重考虑该方案）
