#include "2d_draw.h"
int tg_DrawLine(int b_x, int b_y, int e_x, int e_y, tgra_win* canvas)
{
	int w = canvas->get_w();
	int* pixel = canvas->GetPixels();
	for (int i = b_x; i < e_x; i++)
	{
		int offset = i * w;
		for (int j = b_y; j < e_y; j++)
		{
			pixel[offset+j] = RGB(255, 0, 0);
		}
	}
	return 0;
};