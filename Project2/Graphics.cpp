#include "Graphics.h"
#include <iostream>
bool Graphics::set_pixel(int vec, int rgb)
{
	if (vec<0 || vec>len)return false;
	ptr[vec] = rgb;
	return true;
}
//*
void Graphics::drawpic(Image img, int x, int y, int delta_x, int delta_y)
{
	int offset = (h - x + 1) * w;
	int z = x > 0 ? 0 : -x;
	for (int i = y > 0 ? 0 : -y; i < delta_y && i + y < h; i++)
	{
		offset -= w;
		if (offset<0 || offset>len)continue;
		int kt = img.height * i / delta_y * img.width;
		for (int j = z; j < delta_x && j + x < w; j++)
		{
			set_pixel(offset + j + y, img.get_color(kt + (y + j) * img.width / delta_x));
		}
	}
}
/*
void Graphics::drawpic(Image img, int x, int y, int delta_x, int delta_y)
{
	int offset = (h - x) * w + w;
	float k = img.height / float(delta_y);
	float dk = -k;
	for (int i = 0; i < delta_y; i++)
	{
		offset -= w;
		dk += k;
		if (offset<0 || offset>len)continue;
		int kt = dk ;
		kt *= img.width;
		for (int j = 0; j < delta_x && j < w; j++)
		{
			set_pixel(offset + j, img.get_color(kt + j*img.width/delta_x));
		}
	}
}
//*/
int Graphics::init(int width,int height)
{
	frameCount = 0;
	return reset(width,height);
}
int Graphics::reset(int width,int height)
{
	w = width;                 // 宽度
	h = height;                // 高度
	len = w * h;
	ptr = (int*)malloc(width * height * 4);  // 4字节per像素
	z_ptr = (int*)malloc(width * height * 4);  // 4字节per像素
	return 0;
}
template<typename T>
void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
tg_vec2d* Graphics::line(tg_vec2d begin, tg_vec2d end, int& l_s)
{
	l_s = 0;
	float d1 = 0, d2 = 0, m = begin.far_2(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m;
	tg_vec2d u(begin);
	tg_vec2d* d = new tg_vec2d[m * 3];
	d[l_s] = u;
	l_s++;
	while (!(u == end))
	{
		bool c = 0;
		d1 += k1; d2 += k2;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (d2 >= 1) { u.y++; d2--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	return d;
}
tg_vec2d* Graphics::line_2(tg_vec2d begin, tg_vec2d end, int& l_s)
{
	l_s = 0;
	float d1 = 0, d2 = 0, m = begin.far_2(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m;
	tg_vec2d u(begin);
	tg_vec2d* d = new tg_vec2d[begin.far_with(end) + 3];
	d[l_s] = u;
	l_s++;
	while (!(u.x == end.x && u.y == end.y))
	{
		bool c = 0;
		d1 += k1; d2 += k2;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	float dz = 0, kz = (end.z - begin.z) / (1.0 * l_s);
	for (int i = 0; i < l_s; i++)
	{
		d[i].z += dz;
		dz += kz;
	}
	return d;
}
tg_vec3d* Graphics::line_3(tg_vec3d begin, tg_vec3d end, int& l_s)
{
	if (begin.y > end.y)swap(begin, end);
	l_s = 0;
	float d1 = 0, d2 = 0, d3 = 0, m = begin.far_3(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m, k3 = (end.z - begin.z) / m;
	tg_vec3d u(begin);
	tg_vec3d* d = new tg_vec3d[m * 3 + 10];
	d[l_s] = u;
	l_s++;
	while (!(u == end))
	{
		bool c = 0;
		d1 += k1; d2 += k2; d3 += k3;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d3 <= -1) { u.z--; d3++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (d2 >= 1) { u.y++; d2--; c = 1; }
		if (d3 >= 1) { u.z++; d3--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	return d;
}
int Graphics::tg_DrawLine(tg_vec2d begin, tg_vec2d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	for (auto it = 0; it != l_s; it++)
	{
		ptr[int(d[it].x * w + d[it].y)] = RGB(255, 0, 0);
	}
	delete d;
	return 0;
};
bool Graphics::get_color(tg_vec3d& b, tg_vec3d& e, tg_vec2d& t, float z, int& rgb)
{
	tg_vec3d k(b);
	k.z += (e.z - b.z) * z;
	if (k.z < 0 || (z_ptr[rgb] != -1 && z_ptr[rgb] < k.z))return 0;
	k.x += (e.x - b.x) * z;
	k.y += (e.y - b.y) * z;
	z_ptr[rgb] = k.z;
	ptr[rgb] = RGB(255, 0, 255 - k.z);
	return 1;
}

bool Graphics::get_color_2(tg_vec2d& b, tg_vec2d& e, int z, int offset)
{
	tg_vec3d k(b);
	if (e.x == b.x)return 0;
	float d = (z - b.x) / (1.0 * (e.x - b.x));
	k.z += (e.z - b.z) * d;
	if (k.z < 0 || (z_ptr[offset] != -1 && z_ptr[offset] < k.z))return 0;
	k.x += (e.x - b.x) * d;
	k.y += (e.y - b.y) * d;
	z_ptr[offset] = k.z;
	ptr[offset] = RGB(255, 0, 255 - k.z);
	return 1;
}
int Graphics::tg_DrawLine3d(tg_vec3d begin, tg_vec3d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	int rgb;
	for (int it = 0; it != l_s; it++)
	{
		k++;
		rgb = d[it].x * w + d[it].y;
		get_color(begin, end, d[it], it / (l_s * 1.0), rgb);
	}
	if (l_s > 1)delete d;
	return 0;
};
int Graphics::tg_fill(tg_vec2d* l1, tg_vec2d* l2, int l1_s, int l2_s)
{
	if (l1[0].y > l2[0].y) { swap(l2, l1); swap(l1_s, l2_s); }
	int i = 0, j = 0;
	int t1 = 0, t2 = 0, offest, z;
	while (l1[i].x < l2[j].x)
	{
		i++; if (i == l1_s)return 0;
	}
	while (1)
	{
		while (l1[i].x > l2[j].x)
		{
			j++; if (j == l2_s)return 0;
		}
		offest = l1[i].x * w;
		for (z = l1[i].y; z < l2[j].y; z++) {
			if (z == l1[i].y || z + 1 >= l2[j].y)
				ptr[offest + z] = RGB(0, 0, 125);
		}
		do { i++; if (i == l1_s)return 0; } while (l1[i].x == l1[i - 1].x);
	}
	return 0;
};
int Graphics::tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3)
{
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line(v1, v2, ls1);
	tg_vec2d* l2 = line(v3, v2, ls2);
	tg_vec2d* l3 = line(v1, v3, ls3);
	tg_fill(l1, l2, ls1, ls2);
	tg_fill(l3, l2, ls3, ls2);
	tg_fill(l1, l3, ls1, ls3);
	delete l1;
	delete l2;
	delete l3;
	return 0;
}
int Graphics::tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3)
{
	tg_vec2d vec1(v1), vec2(v2), vec3(v3);
	if (vec1.y < vec2.y)swap(vec1, vec2);
	if (vec2.y < vec3.y) { swap(vec2, vec3); if (vec1.y < vec2.y)swap(vec1, vec2); }
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line_2(vec1, vec2, ls1);
	tg_vec2d* l2 = line_2(vec2, vec3, ls2);
	tg_vec2d* l3 = line_2(vec1, vec3, ls3);
	int len1 = 0, len2 = 0, d;
	d = vec3.x + (vec1.x - vec3.x) * (vec2.y - vec3.y) / (vec1.y - vec3.y);
	if (d < vec2.x)d = 1; else d = -1;
	bool t = 0;
	while (len1 < ls3)
	{
		int offset = l3[len1].y * w;
		for (int x = l3[len1].x; x != l1[len2].x; x += d)
		{
			get_color_2(l3[len1], l1[len2], x, offset + x);
		}
		do { len1++; } while (len1 < ls3 && l3[len1].y == l3[len1 - 1].y);
		do { len2++; } while (len2 < ls1 && l1[len2].y != l3[len1].y);
		if (len2 == ls1 && t == 0) {
			len2 = 0;
			swap(l1, l2); swap(ls1, ls2);
			while (len2 < ls1 && l1[len2].y != l3[len1].y)len2++;
		}
	}
	/*
	for (auto it = 0; it != ls1; it++)
	{
		ptr[int(l1[it].x * w + l1[it].y)] = RGB(0, 0, 0);
	}
	for (auto it = 0; it != ls2; it++)
	{
		ptr[int(l2[it].x * w + l2[it].y)] = RGB(0, 0, 0);
	}
	for (auto it = 0; it != ls3; it++)
	{
		ptr[int(l3 [it] .x * w + l3[it].y)] = RGB(0, 0, 0);
	}
*/
	delete l1;
	delete l2;
	delete l3;
	return 0;
}

