#include"tgra_win.h"
#include <time.h>
#include<iostream>
tgra_win* l;

void u()
{
	l->GetCanvas()->tg_DrawTrangle(tg_vec2d(0, 0), tg_vec2d(l->get_h() / 2, l->get_w()), tg_vec2d(0, l->get_w()));
	l->GetCanvas()->tg_DrawTrangle(tg_vec2d(0, 0), tg_vec2d(l->get_h() / 2, l->get_w()), tg_vec2d(l->get_h() / 2, 0));
}
int main() {
	l = new tgra_win(L"第0列", 400, 400); 
	l->insert(u);
	l->loop();
	return 0;
}

//新的迭代思路，line的返回值变成int*，数组遍历为vector遍历的1/6才。