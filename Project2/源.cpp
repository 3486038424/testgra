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
	l = new tgra_win(L"��0��", 400, 400);
	l->insert(u);
	l->one_loop();
	l->loop();
	return 0;
}

//����֮һ��Ŀǰ�¼������ɴ��ڽ�����ʹ��void�պ�������Ҫ�����޸ģ��������ӳ�������ơ�
//��ȥ���������⣬����������ֵ���룬������ʣ������ԡ���������Ϊ����ָ�룬���뺯�����ֶ��任ָ�롣(���ǵ��߰汾��c++ѧϰ�ɱ������ؿ��Ǹ÷�����
