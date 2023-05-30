
#include"tgra_win.h"
#include <time.h>
#include<iostream>
#include"2d_draw.h"
tgra_win* l;
void update()
{
	l->GetCanvas().tg_DrawLine(l->get_w() / 2, l->get_h() / 2, l->get_w(), l->get_h());
}
void u()
{
	l->GetCanvas().tg_DrawLine(l->get_w() / 2, 0 , l->get_w(), l->get_h()/2);
}
int main() {
	l = new tgra_win(L"╣з0ап", 400, 400); 
	l->insert(update);
	l->insert(u);
	l->loop();
	return 0;
}