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
		
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 120), tg_vec3d(300, 300, 120), tg_vec3d(100, 300, 120));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 120), tg_vec3d(300, 300, 120), tg_vec3d(300, 100, 120));


		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 200), tg_vec3d(300, 300, 200), tg_vec3d(100, 300, 200));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 200), tg_vec3d(300, 300, 200), tg_vec3d(300, 100, 200));


		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 120), tg_vec3d(100, 300, 200), tg_vec3d(100, 300, 120));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 120), tg_vec3d(100, 300, 200), tg_vec3d(100, 100, 200));

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 120), tg_vec3d(300, 100, 200), tg_vec3d(300, 100, 120));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(100, 100, 120), tg_vec3d(300, 100, 200), tg_vec3d(100, 100, 200));

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(300, 300, 120), tg_vec3d(100, 300, 200), tg_vec3d(100, 300, 120));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(300, 300, 120), tg_vec3d(100, 300, 200), tg_vec3d(300, 300, 200));

		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(300, 300, 120), tg_vec3d(300, 100, 200), tg_vec3d(300, 100, 120));
		l->GetCanvas()->tg_DrawTriangle_3d(tg_vec3d(300, 300, 120), tg_vec3d(300, 100, 200), tg_vec3d(300, 300, 200));
		k++;
		*/
		l->GetCanvas()->drawpic(i,-100,-100,500,700);
	}

int main() {
	
	l = new tgra_win(L"��0��", 600, 700);
	l->insert(u);
	l->loop();
	
	return 0;
}

//����֮һ��Ŀǰ�¼������ɴ��ڽ�����ʹ��void�պ�������Ҫ�����޸ģ��������ӳ�������ơ�
//��ȥ���������⣬����������ֵ���룬������ʣ������ԡ���������Ϊ����ָ�룬���뺯�����ֶ��任ָ�롣(���ǵ��߰汾��c++ѧϰ�ɱ������ؿ��Ǹ÷�����
