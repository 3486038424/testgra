#include "tg_vec3d.h"
#include "tg_vec2d.h"
#include <math.h>
float tg_vec3d::far_3(tg_vec3d& t)
{
	float m = 0;
	if (x > t.x)m += pow(x - t.x, 2); else m += pow(t.x - x, 2);
	if (y > t.y)m += pow(y - t.y, 2); else m += pow(t.y - y, 2);
	if (z > t.z)m += pow(z - t.z, 2); else m += pow(t.z - z, 2);
	return pow(m,0.5);
}

tg_vec3d::tg_vec3d(tg_vec2d tg) { x = tg.x * tg.z / 100; y = tg.y * tg.z / 100; z = tg.z; }