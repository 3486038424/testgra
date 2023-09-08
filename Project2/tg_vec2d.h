#pragma once
#include "tg_vec3d.h"
class tg_vec2d
{
public:
	int x;
	int y;
	float z;
	tg_vec2d(float x1 = 0, float x2 = 0) :x(x1), y(x2) {  };
	tg_vec2d(float x1, float x2,float x3) :x(x1/x3), y(x2/x3) {  };
	tg_vec2d(tg_vec3d tg) :x(tg.x / tg.z*100), y(tg.y / tg.z*100) {};
	bool operator==(const tg_vec2d& t)
	{
		return x < t.x+0.002&& x > t.x-0.002 && y > t.y-0.002&& y<t.y+0.002;
	}
	float far_2(tg_vec2d& t);
};

