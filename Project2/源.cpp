#pragma once
//#pragma GCC optimize(2)
#include"tgra_win.h"
#include <time.h>
#include<iostream>
tgra_win* l;
Image i("E://t.png");
int k = 0;
	void u()
	{
		/*
		int t = clock();

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 100), tg_vec3d(600, 600, 100), tg_vec3d(100, 600, 100));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 100), tg_vec3d(600, 600, 100), tg_vec3d(600, 100, 100));


		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 200), tg_vec3d(600, 600, 200), tg_vec3d(100, 600, 200));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 200), tg_vec3d(600, 600, 200), tg_vec3d(600, 100, 200));


		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 100), tg_vec3d(100, 600, 200), tg_vec3d(100, 600, 100));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 100), tg_vec3d(100, 600, 200), tg_vec3d(100, 100, 200));

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 100), tg_vec3d(600, 100, 200), tg_vec3d(600, 100, 100));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 100), tg_vec3d(600, 100, 200), tg_vec3d(100, 100, 200));

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(600, 600, 100), tg_vec3d(100, 600, 200), tg_vec3d(100, 600, 100));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(600, 600, 100), tg_vec3d(100, 600, 200), tg_vec3d(600, 600, 200));

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(600, 600, 100), tg_vec3d(600, 100, 200), tg_vec3d(600, 100, 100));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(600, 600, 100), tg_vec3d(600, 100, 200), tg_vec3d(600, 600, 200));
		k++;
		l->GetCanvas()->drawpic(i,-100,-100,500,700);

		l->GetCanvas()->get_gra().tg_DrawTriangle_3d_with_image(tg_vec3d(100, 600, 200), tg_vec3d(400, 600, 100), tg_vec3d(100, 100, 200), i, tg_vec2d(0, 0), tg_vec2d(i.width, 0), tg_vec2d(0, i.height));
		l->GetCanvas()->get_gra().tg_DrawTriangle_3d_with_image(tg_vec3d(400, 600, 100), tg_vec3d(100, 100, 200), tg_vec3d(400, 100, 100), i, tg_vec2d(i.width, 0), tg_vec2d(i.width, i.height), tg_vec2d(0, i.height));

		*/		

		l->GetCanvas()->get_gra().tg_DrawTriangle_3d_with_image(tg_vec3d(100, 560, 100), tg_vec3d(500, 600, 100), tg_vec3d(100, 100, 100), i, tg_vec2d(0, 0), tg_vec2d(i.width, 0), tg_vec2d(0, i.height));
		l->GetCanvas()->get_gra().tg_DrawTriangle_3d_with_image(tg_vec3d(500, 600, 100), tg_vec3d(500, 100, 100), tg_vec3d(100, 100, 100), i, tg_vec2d(i.width, 0), tg_vec2d(i.width, i.height), tg_vec2d(0, i.height));

	}

int main() {
	
	l = new tgra_win(L"��0��", 600, 700);
	l->insert(u);
	l->one_loop();
	l->loop();
	return 0;
}

//����֮һ��Ŀǰ�¼������ɴ��ڽ�����ʹ��void�պ�������Ҫ�����޸ģ��������ӳ�������ơ�
//��ȥ���������⣬����������ֵ���룬������ʣ������ԡ���������Ϊ����ָ�룬���뺯�����ֶ��任ָ�롣(���ǵ��߰汾��c++ѧϰ�ɱ������ؿ��Ǹ÷�����
