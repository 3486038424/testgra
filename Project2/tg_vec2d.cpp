#include "tg_vec2d.h"
#include <math.h>
float tg_vec2d::far_2(tg_vec2d& t)
{
	return pow(pow(x-t.x,2)+pow(y-t.y,2), 0.5);
}