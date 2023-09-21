#pragma once
#include <iostream>
class tg_vec2d
{
public:
	int x;
	int y;
	tg_vec2d(float x1 = 0, float x2 = 0) :x(x1), y(x2) {  };
	void to_str() { std::cout << x << ' ' << y << '\n'; }
	bool operator==(const tg_vec2d& t)
	{
		return x < t.x+0.002&& x > t.x-0.002 && y > t.y-0.002&& y<t.y+0.002;
	}
	float far_2(tg_vec2d& t);
	int far_with(tg_vec2d& t)
	{
		int x1 = t.x - x, y1 = t.y - y;
		if (x1 < 0)x1 = -x1; if (y1 < 0)y1 = -y1;
		return x1 + y1;
	}
};

