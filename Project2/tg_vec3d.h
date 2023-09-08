#pragma once
class tg_vec2d;
class tg_vec3d
{
public:
	float x, y;
	float z;
	tg_vec3d(float x1 = 0, float x2 = 0,float x3 = 0) :x(x1), y(x2), z(x3) {};
	tg_vec3d(tg_vec2d tg) ;
    bool operator==(const tg_vec3d& t)
    {
		return x == t.x && y == t.y && z == t.z;
    }
	float far_3(tg_vec3d &t);
};

