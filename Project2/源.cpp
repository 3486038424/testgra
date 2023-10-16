#pragma once
#include"tgra_win.h"
#include<random>
tgra_win* l;
//Image i("E://t.png");
int k = 0;
tg_vec2d* vecs;
int wheel = 125;
Graphics* gra;
tg_font t_font;
void u()
{
	gra=l->GetCanvas(0)->get_gra();
	gra->background(RGBA(0, 0, 0, 0));
	POINT mouse = l->get_Frame(0)->get_mouse();
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
	gra->tg_DrawCircle(mouse.x,mouse.y, 8);
	//std::u16string text = u"Hello 世界";
	
	char16_t* text = (char16_t*)u"Hello 世界!";

	t_font.render_text(gra, text, 128, 10);
}

int main() {
	t_font.active_line();
	vecs = new tg_vec2d[10];
	for (int i = 0; i < 10; i++)
	{
		vecs[i] = tg_vec2d(rand()/ (float)RAND_MAX*400,0);
	}
	l = new tgra_win();
	l->frameRate(100);
	l->new_tg_Frame(L"第0列", 400, 400);
	l->insert(u);
	l->GetCanvas(0)->get_gra()->fill(RGBA(255, 255, 255, 0));
	l->loop();
	return 0;
}