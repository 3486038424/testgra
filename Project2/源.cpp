#include"tgra_win.h"
#include <time.h>
#include<iostream>
tgra_win* l;

void u()
{
	l->GetCanvas()->tg_DrawTrangle(0, 0, l->get_h() / 10, l->get_w(), 0, l->get_w());
	l->GetCanvas()->tg_DrawTrangle(0, 0, l->get_h() / 2, l->get_w(), l->get_h()/2, 0);
}
int main() {
	l = new tgra_win(L"╣з0ап", 400, 400); 
	l->insert(u);
	l->loop();
	return 0;
}