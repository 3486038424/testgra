#include "tg_vec3d.h"
#include "tg_vec2d.h"
#include <math.h>
float tg_vec3d::far_3(tg_vec3d& t)
{
	return sqrt(pow(x - t.x, 2) + pow(y - t.y, 2) + pow(z - t.z, 2));
}

tg_vec3d::tg_vec3d(tg_vec2d tg) { x = tg.x * tg.z / 100; y = tg.y * tg.z / 100; z = tg.z; }