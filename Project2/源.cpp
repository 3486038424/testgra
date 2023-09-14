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
	
	l = new tgra_win(L"第0列", 600, 700);
	l->insert(u);
	l->loop();
	
	return 0;
}

//问题之一，目前事件链依旧存在仅可以使用void空函数，需要进行修改，考虑增加抽象类控制。
//除去抽象类以外，考虑增加数值传入，不算合适，但可以。抽象类作为传参指针，进入函数后手动变换指针。(考虑到高版本的c++学习成本，慎重考虑该方案）
