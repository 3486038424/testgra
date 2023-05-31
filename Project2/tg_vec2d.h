#pragma once
#include "tg_vec3d.h"
class tg_vec2d
{
public:
	float x;
	float y;
	tg_vec2d(float x1 = 0, float x2 = 0) :x(x1), y(x2) {  };
	tg_vec2d(float x1, float x2,float x3) :x(x1/x3), y(x2/x3) {  };
	tg_vec2d(tg_vec3d tg) :x(tg.x / tg.z), y(tg.y / tg.z) {};
};

