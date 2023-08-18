#include "tg_vec2d.h"
#include <math.h>
float tg_vec2d::far_2(tg_vec2d& t)
{
	float m = 0;
	if (x > t.x)m += pow(x - t.x, 2); else m += pow(t.x - x, 2);
	if (y > t.y)m += pow(y - t.y, 2); else m += pow(t.y - y, 2);
	return pow(m, 0.5);
}